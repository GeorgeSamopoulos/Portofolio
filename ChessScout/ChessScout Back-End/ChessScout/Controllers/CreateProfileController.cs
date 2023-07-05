using ChessScout.Models;
using HtmlAgilityPack;
using Microsoft.AspNetCore.Mvc;
using Microsoft.Data.SqlClient;
using Microsoft.EntityFrameworkCore.Metadata.Internal;
using Microsoft.Extensions.Caching;
using Microsoft.Extensions.Caching.Memory;
using Newtonsoft.Json;
using System.Collections.Generic;
using System.Data;
using System.IO;
using System.Text.RegularExpressions;
using System.Web.Helpers;

namespace ChessScout.Controllers
{
    
    public class GlobalList
    {
        public static string name { get; set; }
        public static int lastYear { get; set; }
        public static int startYear { get; set; }
        public static int elo { get; set; }
        public static int Pid { get; set;}
        public static List<GameDetails> AllGames = new List<GameDetails>();
        public static List<GameDetails> UseGames = new List<GameDetails>();
    }


    [ApiController]
    [Route("api/[controller]")]
    public class CreateProfileController : ControllerBase
    {
        private readonly IMemoryCache _cache;

        private readonly ChessScoutDbContext _dbcontext;
        public CreateProfileController(ChessScoutDbContext _context, IMemoryCache cache)
        {
            _dbcontext = _context;
            _cache = cache;

        }

        [HttpGet]
        [Route("/CreateProfile")]
        public async Task<IActionResult> GetGamesAsync()
        {
            Console.WriteLine("The application started at {0:HH:mm:ss.fff}", DateTime.Now);
            String firstname = Request.Query["firstname"].ToString();
            String lastname = Request.Query["lastname"].ToString();
            String color = Request.Query["color"].ToString();

            var url = "https://www.chessgames.com/perl/ezsearch.pl?search="+firstname+"+"+lastname;

            HtmlWeb web = new HtmlWeb();
            HtmlDocument doc = web.Load(url);
            string page = doc.DocumentNode.OuterHtml;


            /*=====Search for pid=====*/
            string subStr = "pid=";
            int pos = page.IndexOf(subStr)+4;
            if (pos==-1) {
            
            }
            int i = 0;
            string pid = "";
            while (page[pos + i] != '\"')
            {
                pid += page[pos + i++];

            }

            
            int num_pid = Int32.Parse(pid);
            GlobalList.Pid = num_pid;
            FindPlayer(num_pid);

            

            /*=====Search for number of pages=====*/
            int pagei = page.IndexOf("page 1 of ") + 10;
            i = 0;
            string pages = "";
            while (page[pagei + i] != ';')
            {
                pages += page[pagei + (i++)];
            }

            int num_pages = Int32.Parse(pages);


            /*=====Search for gids=====*/
            List<GameDetails> Games = new List<GameDetails>();
            if (num_pages > 6)
            {
                List<GameDetails> GameDetails1 = new List<GameDetails>();
                List<GameDetails> GameDetails2 = new List<GameDetails>();
                List<GameDetails> GameDetails3 = new List<GameDetails>();

                Thread thread1 = new Thread(() => GameDetails1 = GetGid(1, num_pages / 3, num_pid));
                Thread thread2 = new Thread(() => GameDetails2 = GetGid((num_pages / 3) + 1, (num_pages * 2) / 3, num_pid));
                Thread thread3 = new Thread(() => GameDetails3 = GetGid(((num_pages * 2) / 3) + 1, num_pages, num_pid));
                thread1.Start();
                thread2.Start();
                thread3.Start();

                thread1.Join();
                thread2.Join();
                thread3.Join();

                GameDetails2.AddRange(GameDetails1);
                GameDetails3.AddRange(GameDetails2);
                Games.AddRange(GameDetails3);

                
            }
            else
            {
                List<GameDetails> GameDetails = new List<GameDetails>();
                GameDetails = GetGid(1, num_pages, num_pid);
                Games.AddRange(GameDetails);
            }
            
            Console.WriteLine("Done Games");

            Console.WriteLine("The application ended at {0:HH:mm:ss.fff}", DateTime.Now);
            string jsongames = JsonConvert.SerializeObject(Games);
            _cache.Set("games" + pid, jsongames);

            /*COLOR CHOOSE*/
            List<GameDetails> UseGames = new List<GameDetails>();
            UseGames = GamesByColor(color,GlobalList.name);
            UseGames = UseGames.OrderBy(o => o.year).ToList();
            string jsonusedgames =  JsonConvert.SerializeObject(UseGames);
            _cache.Set("usedgames" + GlobalList.Pid.ToString(), jsonusedgames);
            string json = JsonConvert.SerializeObject(UseGames);
            return Content(json, "application/json");
        }

        List<GameDetails> GamesByColor(string color,string name)
        {
            
            List<GameDetails> games = new List<GameDetails>();
            Console.WriteLine("GamesByColor");
            string jsongames = (string)_cache.Get("games" + GlobalList.Pid.ToString());

            List< GameDetails > AllGames = JsonConvert.DeserializeObject<List<GameDetails>>(jsongames);
            int i;
            int pos = name.IndexOf(' ')+1; 
            string lastname = name.Substring(pos, name.Length-pos).ToLower();
            Console.WriteLine(lastname);
            if (color == "White")
            {
                foreach (GameDetails g in AllGames)
                {
                    string white_player = g.White_Player.ToLower();
                    pos = white_player.IndexOf(lastname);
                    if (pos!=-1) { 
                        games.Add(g);
                    }
                }
            }
            else if (color == "Black")
            {
                foreach (GameDetails g in AllGames)
                {
                    string black_player = g.Black_Player.ToLower();
                    pos = black_player.IndexOf(lastname);
                    if (pos != -1)
                    {
                        games.Add(g);
                    }
                }

            }
            else { 
            
                return AllGames;
            
            }


            return games;
        }

         List<GameDetails> GetGid(int start , int end ,int pid)
        {
            int i = 0;
            string url;
            HtmlWeb web = new HtmlWeb();
            HtmlDocument doc;
            List<GameDetails> GameDetails = new List<GameDetails>();
            for (i = start; i <= end; i++)
            {
                List<GameDetails> GamesTemp = new List<GameDetails>();
                url = "https://www.chessgames.com/perl/chess.pl?page=" + i + "&pid=" + pid;
                doc = web.Load(url);
                GamesTemp = PageGamesDetails(doc);
                GameDetails.AddRange(GamesTemp);
            }
            return GameDetails;
        }


        List <GameDetails> PageGamesDetails(HtmlDocument doc)
        {
            IEnumerable <HtmlNode> gamelist1 = doc.DocumentNode.SelectNodes("//tr").Where(div => div.Attributes["bgcolor"]?.Value == "#FFFFFF");
            IEnumerable<HtmlNode> gamelist2 = doc.DocumentNode.SelectNodes("//tr").Where(div => div.Attributes["bgcolor"]?.Value == "#EEDDCC");

            List <GameDetails> gamedetails = new List<GameDetails>();
            
            foreach (HtmlNode n in gamelist1)
            {

                string data = n.OuterHtml;
                int pos = data.IndexOf("gid=")+4;
                data = data.Substring(pos,data.Length-pos);
                int j = 0;
                string gid = "";
                while (data[j] != '\"')
                {
                    gid += data[j];
                    j++;
                }

                pos = data.IndexOf(">")+1;
                data = data.Substring(pos, data.Length - pos);
                j = 0;
                string names = "";
                while (data[j] != '<')
                {
                    names += data[j];
                    j++;
                }

                string white = "";
                string black = "";
                pos = names.IndexOf("vs");
                j = 0;
                while (j!=(pos-1)) {
                    white += names[j];
                    j++;
                }

                

                pos = names.IndexOf("vs")+3;
                j = pos;
                while (j != names.Length)
                {
                    black += names[j];
                    j++;
                }

                pos = data.IndexOf("size=\"-1\"") + 10;
                data = data.Substring(pos, data.Length - pos);
                j = 0;
                string result = "";
                while (data[j] != '<')
                {
                    result += data[j];
                    j++;
                }

                if (result == "&#189;-&#189;")
                {
                    result="0.5-0.5";
                }
                pos = data.IndexOf("size=\"-1\"") + 10;
                data = data.Substring(pos, data.Length - pos);
                j = 0;
                string moves = "";
                while (data[j] != '<')
                {
                    moves += data[j];
                    j++;
                }


                pos = data.IndexOf("size=\"-1\"") + 10;
                data = data.Substring(pos, data.Length - pos);
                j = 0;
                string year = "";
                while (data[j] != '<')
                {
                    year += data[j];
                    j++;
                }

                pos = data.IndexOf("eco=") + 4;
                j = pos;
                string eco = "";
                while (data[j] != '\"')
                {
                    eco += data[j];
                    j++;
                }

                pos = data.IndexOf("tid=") + 4;
                data = data.Substring(pos, data.Length - pos);
                j = 0;
                while (data[j] != '>')
                {
                    j++;
                }
                pos = j + 1;

                string tour = "";
                j = pos;
                while (data[j] != '<')
                {
                    tour += data[j];
                    j++;
                }

                //-------------- EDW KWDIKA GIA KATHE PAIXNIDI APO LISTA 1 
                gamedetails.Add(new GameDetails(Int32.Parse(gid),white,black,result, Int32.Parse(moves), Int32.Parse(year),eco,tour));
            }

            foreach (HtmlNode n in gamelist2)
            {
                string data = n.OuterHtml;

                int pos = data.IndexOf("gid=") + 4;
                data = data.Substring(pos, data.Length - pos);
                int j = 0;
                string gid = "";
                while (data[j] != '\"')
                {
                    gid += data[j];
                    j++;
                }
                pos = data.IndexOf(">") + 1;
                data = data.Substring(pos, data.Length - pos);
                j = 0;
                string names = "";
                while (data[j] != '<')
                {
                    names += data[j];
                    j++;
                }
                string white = "";
                string black = "";
                pos = names.IndexOf("vs");
                j = 0;
                while (j != (pos - 1))
                {
                    white += names[j];
                    j++;
                }



                pos = names.IndexOf("vs") + 3;
                j = pos;
                while (j != names.Length)
                {
                    black += names[j];
                    j++;
                }


                pos = data.IndexOf("size=\"-1\"") + 10;
                data = data.Substring(pos, data.Length - pos);
                j = 0;
                string result = "";
                while (data[j] != '<')
                {
                    result += data[j];
                    j++;
                }

                if (result == "&#189;-&#189;")
                {
                    result = "0.5-0.5";
                }

                pos = data.IndexOf("size=\"-1\"") + 10;
                data = data.Substring(pos, data.Length - pos);
                j = 0;
                string moves = "";
                while (data[j] != '<')
                {
                    moves += data[j];
                    j++;
                }


                pos = data.IndexOf("size=\"-1\"") + 10;
                data = data.Substring(pos, data.Length - pos);
                j = 0;
                string year = "";
                while (data[j] != '<')
                {
                    year += data[j];
                    j++;
                }
                pos = data.IndexOf("eco=") + 4;
                j = pos;
                string eco = "";
                while (data[j] != '\"')
                {
                    eco += data[j];
                    j++;
                }

                pos = data.IndexOf("tid=") + 4;
                data = data.Substring(pos, data.Length - pos);
                j = 0;
                while (data[j] != '>')
                {
                    j++;
                }
                pos = j + 1;

                string tour = "";
                j = pos;
                while (data[j] != '<')
                {
                    tour += data[j];
                    j++;
                }

                //-------------- EDW KWDIKA GIA KATHE PAIXNIDI APO LISTA 2
                gamedetails.Add(new GameDetails(Int32.Parse(gid), white, black, result, Int32.Parse(moves), Int32.Parse(year), eco, tour));

            }


            return gamedetails;
        }

        [HttpGet]
        [Route("/DownloadGame")]
        public async Task<IActionResult> DownloadGame()
        {
            string gid = Request.Query["gid"].ToString();
            HtmlWeb web = new HtmlWeb();
            HtmlDocument doc;
            string url = "https://www.chessgames.com/perl/chessgame?gid=" + gid;
            doc = web.Load(url);
            HtmlNode divNode = doc.DocumentNode.SelectSingleNode("//div[@id='olga-data']");

            string pgn = divNode.Attributes["pgn"].Value;
            string json = "";
            int num = Int32.Parse(gid);
            List<GameDetails> ret = new List<GameDetails>();
            string jsongames = (string)_cache.Get("games"+GlobalList.Pid.ToString());
            List<GameDetails> AllGames = JsonConvert.DeserializeObject<List<GameDetails>>(jsongames);
            foreach (GameDetails g in AllGames)
            {

                if (g.Gid == num) {
                    Console.WriteLine("ok");
                    g.addGamePgn(pgn);
                    ret.Add(g);
                }
            }

            json = JsonConvert.SerializeObject(ret);
            return Content(json, "application/json");
            
        }

        [HttpGet]
        [Route("/CalculateByName")]
        public async Task<IActionResult> CalculateName()
        {
            Console.WriteLine("Calculate name");

            string json = "";
            string jsonusedgames = (string)_cache.Get("usedgames" + GlobalList.Pid.ToString());
            List<GameDetails> UseGames = JsonConvert.DeserializeObject<List<GameDetails>>(jsonusedgames);
            if (UseGames.Count == 0)
            {
                Console.WriteLine("In");
                return Content(json, "application/json");
            }
            Dictionary<string, string> ECOMAP = init_ECO_MAP();
            Dictionary<string, int> ECOCount = new Dictionary<string, int>();
            Dictionary<string, int> WinRates = new Dictionary<string, int>();
            int total_games = UseGames.Count;
            foreach (string key in ECOMAP.Keys)
            {
                ECOCount.Add(key, 0);
                WinRates.Add(key, 0);
            }

            foreach (GameDetails g in UseGames)
            {
                if (g.ECO != "000")
                {
                    ECOCount[g.ECO]++;
                    if (WinRate(g,GlobalList.name))
                    {
                        WinRates[g.ECO]++;
                    }
                }
            }

            var SortEcoCount = ECOCount.OrderByDescending(e => e.Value).ToList();

            List<DataOpeningName> DataOpening = new List<DataOpeningName>();
            foreach (var item in SortEcoCount)
            {
                if (ECOCount[item.Key] != 0) {
                    double prate = ((double)(ECOCount[item.Key]) / (double)(total_games)) * 100;
                    double wrate = ((double)(WinRates[item.Key]) / (double)(ECOCount[item.Key])) * 100;
                    DataOpening.Add(new DataOpeningName(item.Key, ECOMAP[item.Key], Math.Round(prate, 1), Math.Round(wrate, 1)));
                }
            }
            json = JsonConvert.SerializeObject(DataOpening);
            return Content(json, "application/json");
        }

        bool WinRate(GameDetails g, String name)
        {
            int pos = name.IndexOf(' ') + 1;
            string lastname = name.Substring(pos, name.Length - pos).ToLower();

            string black_player = g.Black_Player.ToLower();
            pos = black_player.IndexOf(lastname);
            if (pos != -1)
            {
                if (g.result=="0-1") {
                    return true;
                }
            }
            else
            {
                Console.WriteLine(lastname);

                string white_player = g.White_Player.ToLower();
                Console.WriteLine(white_player);
                Console.WriteLine(g.result);
                pos = white_player.IndexOf(lastname);
                if(pos != -1)
                {
                    if(g.result=="1-0")
                        return true;
                }
            }


            return false;
        }

        [HttpGet]
        public List<string> ParsePgnString(string pgnString)
        {
            List<string> moves = new List<string>();
            string[] substrings = pgnString.Split("\n1.");
            string movesString = substrings[1];
            string[] movesStrings = movesString.Split(' ');
            int i = 0;
            foreach (string m in movesStrings)
            {

                int pos = m.IndexOf('.');
                if (pos!=-1) {
                    string [] parts = m.Split('.');
                    movesStrings[i] = parts[1];
                }
                i++;
            }

            List<string> movesList = movesStrings.ToList();
            List<int> poss = new List<int>();
            i = 0;
            foreach (string s in movesList) {
                int len = s.Length;
                if (len == 0) {
                    poss.Add(i);
                }
                i++;
            }
            Console.WriteLine("SizeOfList : "+movesList.Count);
            i = 0;
            foreach (int c in poss) {
                movesList.RemoveAt(c-i);
                i++;
            }

            movesList.RemoveAt(movesList.Count - 1);

            return movesList;
        }

        [HttpGet]
        [Route("/CalculateByMove")]
        public async Task<IActionResult> CalculateMove()
        {
            Console.WriteLine("Calculate move");
            
            string json = "";
            string jsongames = (string)_cache.Get("usedgames" + GlobalList.Pid.ToString());
            List<GameDetails> UsedGames = JsonConvert.DeserializeObject<List<GameDetails>>(jsongames);
            if (UsedGames.Count == 0)
            {
                return Content(json, "application/json");
            }

            int gamesdown = 0;
            int i = 0;
            while(gamesdown <= 7){
                if (i>=UsedGames.Count) {

                    break;
                
                }

                if (UsedGames[i].Game == null) {
                    string gid = UsedGames[i].Gid.ToString();
                    HtmlWeb web = new HtmlWeb();
                    HtmlDocument doc;
                    string url = "https://www.chessgames.com/perl/chessgame?gid=" + gid;
                    doc = web.Load(url);
                    HtmlNode divNode = doc.DocumentNode.SelectSingleNode("//div[@id='olga-data']");

                    string pgn = divNode.Attributes["pgn"].Value;
                    UsedGames[i].addGamePgn(pgn);
                    List<string> movelist = ParsePgnString(pgn);
                    UsedGames[i].movelist = new List<string>(movelist);
                    gamesdown++;
                }
                i++;
            }

            json = JsonConvert.SerializeObject(UsedGames);
            _cache.Set("usedgames" + GlobalList.Pid.ToString(), json);

            String depthS = Request.Query["depth"].ToString();
            int depth = Int32.Parse(depthS);

            List<string> movesDepth = new List<string>();
            List<GameDetails> GamesValid = new List<GameDetails>();
            if (depth > 0) {
                String lastMove = Request.Query["last_move"].ToString();
                if (depth == 1)
                {
                    List <string> movesTree= new List<string>();
                    movesTree.Add(lastMove);
                    _cache.Set("movesDepth" + GlobalList.Pid.ToString(), movesTree);
                    movesDepth = new List<string>(movesTree);
                    Console.WriteLine("==========="+depth);
                    foreach (string item in movesDepth)
                    {
                        Console.WriteLine(item);
                    }

                    Console.WriteLine("===========");

                }
                else {
                    List<string> movesTree = (List <string>) _cache.Get("movesDepth" + GlobalList.Pid.ToString());
                    if(depth!=2)    
                        movesTree.Add(lastMove);
                    _cache.Set("movesDepth" + GlobalList.Pid.ToString(), movesTree);
                    movesDepth = new List<string>(movesTree);
                    Console.WriteLine("===========" + depth);
                    foreach (string item in movesDepth)
                    {
                        Console.WriteLine(item);
                    }

                    Console.WriteLine("===========");

                }

                foreach (GameDetails g in UsedGames) {
                    if (g.movelist.Count == 0) {
                        continue;
                    }

                    List<string> testMoves = g.movelist;
                    bool flag = true;
                    int c = 0;
                    foreach (string m in movesDepth) {
                        if (m == testMoves[c])
                        {
                            c++;
                        }
                        else {
                            flag = false;
                            break;
                        }
                    }
                    if (flag) {
                        GamesValid.Add(g);
                    }
                }
            }
            else {
                foreach (GameDetails g in UsedGames) {
                    if (g.movelist.Count!=0) {

                        GamesValid.Add(g);
                    
                    }
                
                }

            }

            Console.WriteLine("Valid Games Number = "+ GamesValid.Count);
            Dictionary<string, int> PRate = new Dictionary<string, int>();
            Dictionary<string, int> WRate = new Dictionary<string, int>();

            foreach (GameDetails g in GamesValid) {
                if (g.movelist.Count <= depth) {
                    continue;
                }
                if (PRate.ContainsKey(g.movelist[depth])) {
                    PRate[g.movelist[depth]]++;
                }
                else
                {
                    PRate.Add(g.movelist[depth],1);
                }

                if (WRate.ContainsKey(g.movelist[depth]))
                {
                    if (WinRate(g,GlobalList.name)) { 
                        WRate[g.movelist[depth]]++;
                    }
                }
                else
                {
                    WRate.Add(g.movelist[depth], 0);
                    if (WinRate(g, GlobalList.name))
                    {
                        WRate[g.movelist[depth]]++;
                    }
                }

            }

            List<MoveTree> resTree = new List<MoveTree>();

            foreach (KeyValuePair<string, int> kvp in PRate) {
                int wr = WRate[kvp.Key];
                int pr = PRate[kvp.Key];

                MoveTree mt = new MoveTree((double)wr / (double)GamesValid.Count, (double)pr / (double)GamesValid.Count, kvp.Key);
                resTree.Add(mt);
            }



            MoveTreeResponse response = new MoveTreeResponse
            {
                NumOfDownloaded = i,
                depth = depth,
                datamoves = resTree
            };

            json = JsonConvert.SerializeObject(response);
            return Content(json, "application/json");
        }


        Dictionary<string, string> init_ECO_MAP()
        {
            Dictionary<string, string> EcoMap = new Dictionary<string, string>();

            EcoMap.Add("A00", "Irregular Openings");
            EcoMap.Add("A01", "Nimzowitsch-Larsen Attack");
            EcoMap.Add("A02", "Bird's Opening");
            EcoMap.Add("A03", "Bird's Opening, 1...e6");
            EcoMap.Add("A04", "Reti Opening");
            EcoMap.Add("A05", "Reti Opening");
            EcoMap.Add("A06", "Reti Opening");
            EcoMap.Add("A07", "King's Indian Attack");
            EcoMap.Add("A08", "King's Indian Attack");
            EcoMap.Add("A09", "Reti Opening");
            EcoMap.Add("A10", "English Opening");
            EcoMap.Add("A11", "English Opening");
            EcoMap.Add("A12", "English Opening");
            EcoMap.Add("A13", "English Opening");
            EcoMap.Add("A14", "English Opening");
            EcoMap.Add("A15", "English Opening");
            EcoMap.Add("A16", "English Opening");
            EcoMap.Add("A17", "English Opening");
            EcoMap.Add("A18", "English Opening");
            EcoMap.Add("A19", "English Opening");
            EcoMap.Add("A20", "English Opening");
            EcoMap.Add("A21", "English Opening");
            EcoMap.Add("A22", "English Opening");
            EcoMap.Add("A23", "English Opening");
            EcoMap.Add("A24", "English Opening");
            EcoMap.Add("A25", "English Opening");
            EcoMap.Add("A26", "English Opening");
            EcoMap.Add("A27", "English Opening");
            EcoMap.Add("A28", "English Opening");
            EcoMap.Add("A29", "English Opening");
            EcoMap.Add("A30", "English Opening");
            EcoMap.Add("A31", "English Opening");
            EcoMap.Add("A32", "English Opening");
            EcoMap.Add("A33", "English Opening");
            EcoMap.Add("A34", "English Opening");
            EcoMap.Add("A35", "English Opening");
            EcoMap.Add("A36", "English Opening");
            EcoMap.Add("A37", "English Opening");
            EcoMap.Add("A38", "English Opening");
            EcoMap.Add("A39", "English Opening");
            EcoMap.Add("A40", "Queen's Pawn Game");
            EcoMap.Add("A41", "Queen's Pawn Game EcoMap.Add(without Nc3);");
            EcoMap.Add("A42", "Modern Defense, Averbakh System");
            EcoMap.Add("A43", "Old Benoni Defense");
            EcoMap.Add("A44", "Old Benoni Defense");
            EcoMap.Add("A45", "Queen's Pawn Game");
            EcoMap.Add("A46", "Queen's Pawn Game");
            EcoMap.Add("A47", "Queen's Indian Defense");
            EcoMap.Add("A48", "King's Indian, East Indian Defense");
            EcoMap.Add("A49", "King's Indian, Fianchetto without c4");
            EcoMap.Add("A50", "Queen's Pawn Game");
            EcoMap.Add("A51", "Budapest Gambit");
            EcoMap.Add("A52", "Budapest Gambit");
            EcoMap.Add("A53", "Old Indian Defense");
            EcoMap.Add("A54", "Old Indian Defense, Ukrainian Variation");
            EcoMap.Add("A55", "Old Indian Defense, Normal Variation");
            EcoMap.Add("A56", "Benoni Defense");
            EcoMap.Add("A57", "Benko Gambit");
            EcoMap.Add("A58", "Benko Gambit");
            EcoMap.Add("A59", "Benko Gambit");
            EcoMap.Add("A60", "Benoni Defense");
            EcoMap.Add("A61", "Benoni Defense, Modern Variation with g3");
            EcoMap.Add("A62", "Benoni Defense, Fianchetto Variation");
	        EcoMap.Add("A63", "Benoni Defense, Flexible Variation");
	        EcoMap.Add("A64", "Benoni Defense, Classical Variation");
	        EcoMap.Add("A65", "Benoni Defense, 6.e4");
            EcoMap.Add("A66", "Benoni Defense, Pawn Storm Variation");
            EcoMap.Add("A67", "Benoni Defense, Taimanov Variation");
            EcoMap.Add("A68", "Benoni Defense, Four Pawns Attack");
            EcoMap.Add("A69", "Benoni Defense, Four Pawns Attack, Main Line");
            EcoMap.Add("A70", "Benoni Defense");
            EcoMap.Add("A71", "Benoni Defense, Classical Variation");
            EcoMap.Add("A72", "Benoni Defense, Classical Variation");
            EcoMap.Add("A73", "Benoni Defense, Classical Variation");
            EcoMap.Add("A74", "Benoni Defense, Classical Variation");
            EcoMap.Add("A75", "Benoni Defense, Classical Variation");
            EcoMap.Add("A76", "Benoni Defense, Classical Variation");
            EcoMap.Add("A77", "Benoni Defense, Classical Variation");
            EcoMap.Add("A78", "Benoni Defense, Classical Variation with ...Re8 and ...Na6");
            EcoMap.Add("A79", "Benoni Defense, Classical Variation with ...Re8 and ...Nc6");
            EcoMap.Add("A80", "Dutch Defense");
            EcoMap.Add("A81", "Dutch Defense");
            EcoMap.Add("A82", "Dutch Defense, Staunton Gambit");
            EcoMap.Add("A83", "Dutch Defense, Staunton Gambit");
            EcoMap.Add("A84", "Dutch Defense, Staunton Gambit, Modern Variation");
            EcoMap.Add("A85", "Dutch Defense, Queen's Knight Variation");
            EcoMap.Add("A86", "Dutch Defense, Leningrad Variation");
            EcoMap.Add("A87", "Dutch Defense, Leningrad Variation, Main Line");
            EcoMap.Add("A88", "Dutch Defense, Leningrad Variation, Warsaw Variation");
            EcoMap.Add("A89", "Dutch Defense, Leningrad Variation, Matulovic Variation");
            EcoMap.Add("A90", "Dutch Defense");
            EcoMap.Add("A91", "Dutch Defense");
            EcoMap.Add("A92", "Dutch Defense");
            EcoMap.Add("A93", "Dutch Defense, Stonewall Variation");
            EcoMap.Add("A94", "Dutch Defense, Classical Variation");
            EcoMap.Add("A95", "Dutch Defense, Stonewall Variation");
            EcoMap.Add("A96", "Dutch Defense, Classical Variation");
            EcoMap.Add("A97", "Dutch Defense, Ilyin-Zhenevsky Variation");
            EcoMap.Add("A98", "Dutch Defense, Ilyin-Zhenevsky Variation with Qh4");
            EcoMap.Add("A99", "Dutch Defense, Ilyin-Zhenevsky Variation with b3");
            EcoMap.Add("B00", "Uncommon King's Pawn Opening");
            EcoMap.Add("B01", "Scandinavian Defense");
            EcoMap.Add("B02", "Alekhine's Defense");
            EcoMap.Add("B03", "Alekhine's Defense, Four Pawns Attack");
            EcoMap.Add("B04", "Alekhine's Defense, Modern Variation");
            EcoMap.Add("B05", "Alekhine's Defense, Modern Variation");
            EcoMap.Add("B06", "Robatsch EcoMap.Add(Modern); Defense");
            EcoMap.Add("B07", "Pirc Defense");
            EcoMap.Add("B08", "Pirc Defense, Classical Variation");
            EcoMap.Add("B09", "Pirc Defense, Austrian Attack");
            EcoMap.Add("B10", "Caro-Kann Defense");
            EcoMap.Add("B11", "Caro-Kann Defense, Two Knights Variation");
            EcoMap.Add("B12", "Caro-Kann Defense, Advance Variation");
            EcoMap.Add("B13", "Caro-Kann Defense, Exchange Variation");
            EcoMap.Add("B14", "Caro-Kann Defense, Panov-Botvinnik Attack");
            EcoMap.Add("B15", "Caro-Kann Defense");
            EcoMap.Add("B16", "Caro-Kann Defense, Bronstein-Larsen Variation");
            EcoMap.Add("B17", "Caro-Kann Defense, Karpov Variation");
            EcoMap.Add("B18", "Caro-Kann Defense, Classical Variation");
            EcoMap.Add("B19", "Caro-Kann Defense, Classical Variation");
            EcoMap.Add("B20", "Sicilian Defense");
            EcoMap.Add("B21", "Sicilian Defense, Smith-Morra Gambit");
            EcoMap.Add("B22", "Sicilian Defense, Alapin Variation");
            EcoMap.Add("B23", "Sicilian Defense, Closed");
            EcoMap.Add("B24", "Sicilian Defense, Closed");
            EcoMap.Add("B25", "Sicilian Defense, Closed");
            EcoMap.Add("B26", "Sicilian Defense, Closed");
            EcoMap.Add("B27", "Sicilian Defense, Hyperaccelerated Fianchetto");
            EcoMap.Add("B28", "Sicilian Defense, O'Kelly Variation");
            EcoMap.Add("B29", "Sicilian Defense, Nimzowitsch Variation");
            EcoMap.Add("B30", "Sicilian Defense, Rossolimo Variation");
            EcoMap.Add("B31", "Sicilian Defense, Rossolimo Variation");
            EcoMap.Add("B32", "Sicilian Defense, Open");
            EcoMap.Add("B33", "Sicilian Defense, Sveshnikov Variation");
            EcoMap.Add("B34", "Sicilian Defense, Accelerated Dragon");
            EcoMap.Add("B35", "Sicilian Defense, Accelerated Dragon");
            EcoMap.Add("B36", "Sicilian Defense, Accelerated Dragon");
            EcoMap.Add("B37", "Sicilian Defense, Accelerated Fianchetto");
            EcoMap.Add("B38", "Sicilian Defense, Accelerated Dragon, Maróczy Bind");
            EcoMap.Add("B39", "Sicilian Defense, Accelerated Fianchetto, Breyer Variation");
            EcoMap.Add("B40", "Sicilian Defense");
            EcoMap.Add("B41", "Sicilian Defense, Kan Variation");
            EcoMap.Add("B42", "Sicilian Defense, Kan Variation");
            EcoMap.Add("B43", "Sicilian Defense, Kan Variation");
            EcoMap.Add("B44", "Sicilian Defense, Paulsen Variation");
            EcoMap.Add("B45", "Sicilian Defense, Taimanov Variation");
            EcoMap.Add("B46", "Sicilian Defense, Taimanov Variation");
            EcoMap.Add("B47", "Sicilian Defense, Taimanov Variation");
            EcoMap.Add("B48", "Sicilian Defense, Taimanov Variation");
            EcoMap.Add("B49", "Sicilian Defense, Taimanov Variation");
            EcoMap.Add("B50", "Sicilian Defense");
            EcoMap.Add("B51", "Sicilian Defense, Canal-Sokolsky EcoMap.Add(Nimzovich-Rossolimo, Moscow); Attack");
            EcoMap.Add("B52", "Sicilian Defense, Canal-Sokolsky EcoMap.Add(Rossolimo); Attack");
            EcoMap.Add("B53", "Sicilian Defense, Chekhover Variation");
            EcoMap.Add("B54", "Sicilian Defense, Prins Variation");
            EcoMap.Add("B55", "Sicilian Defense, Prins Variation");
            EcoMap.Add("B56", "Sicilian Defense, Classical Variation");
            EcoMap.Add("B57", "Sicilian Defense, Classical Variation");
            EcoMap.Add("B58", "Sicilian Defense, Boleslavsky Variation");
            EcoMap.Add("B59", "Sicilian Defense, Boleslavsky Variation");
            EcoMap.Add("B60", "Sicilian Defense, Richter-Rauzer Variation");
            EcoMap.Add("B61", "Sicilian Defense, Richter-Rauzer Variation");
            EcoMap.Add("B62", "Sicilian Defense, Richter-Rauzer Variation");
            EcoMap.Add("B63", "Sicilian Defense, Richter-Rauzer Variation");
            EcoMap.Add("B64", "Sicilian Defense, Richter-Rauzer Variation");
            EcoMap.Add("B65", "Sicilian Defense, Richter-Rauzer Variation");
            EcoMap.Add("B66", "Sicilian Defense, Richter-Rauzer Variation");
            EcoMap.Add("B67", "Sicilian Defense, Richter-Rauzer Variation");
            EcoMap.Add("B68", "Sicilian Defense, Richter-Rauzer Variation");
            EcoMap.Add("B69", "Sicilian Defense, Richter-Rauzer Variation");
            EcoMap.Add("B70", "Sicilian Defense, Dragon Variation");
            EcoMap.Add("B71", "Sicilian Defense, Dragon Variation");
            EcoMap.Add("B72", "Sicilian Defense, Dragon Variation");
            EcoMap.Add("B73", "Sicilian Defense, Dragon Variation");
            EcoMap.Add("B74", "Sicilian Defense, Dragon, Classical Variation");
            EcoMap.Add("B75", "Sicilian Defense, Dragon, Yugoslav Attack");
            EcoMap.Add("B76", "Sicilian Defense, Dragon, Yugoslav Attack");
            EcoMap.Add("B77", "Sicilian Defense, Dragon, Yugoslav Attack");
            EcoMap.Add("B78", "Sicilian Defense, Dragon, Yugoslav Attack");
            EcoMap.Add("B79", "Sicilian Defense, Dragon, Yugoslav Attack");
            EcoMap.Add("B80", "Sicilian Defense, Scheveningen Variation");
            EcoMap.Add("B81", "Sicilian Defense, Scheveningen Variation");
            EcoMap.Add("B82", "Sicilian Defense, Scheveningen Variation");
            EcoMap.Add("B83", "Sicilian Defense, Scheveningen Variation");
            EcoMap.Add("B84", "Sicilian Defense, Scheveningen Variation");
            EcoMap.Add("B85", "Sicilian Defense, Scheveningen Variation");
            EcoMap.Add("B86", "Sicilian Defense, Sozin Attack");
            EcoMap.Add("B87", "Sicilian Defense, Sozin Attack, Flank Variation");
            EcoMap.Add("B88", "Sicilian Defense, Sozin Attack, Leonhardt Variation");
            EcoMap.Add("B89", "Sicilian Defense, Sozin Attack, Main Line");
            EcoMap.Add("B90", "Sicilian Defense, Najdorf Variation");
            EcoMap.Add("B91", "Sicilian Defense, Najdorf Variation");
            EcoMap.Add("B92", "Sicilian Defense, Najdorf Variation");
            EcoMap.Add("B93", "Sicilian Defense, Najdorf Variation");
            EcoMap.Add("B94", "Sicilian Defense, Najdorf Variation");
            EcoMap.Add("B95", "Sicilian Defense, Najdorf Variation");
            EcoMap.Add("B96", "Sicilian Defense, Najdorf Variation");
            EcoMap.Add("B97", "Sicilian Defense, Najdorf Variation, Poisoned Pawn");
            EcoMap.Add("B98", "Sicilian Defense, Najdorf Variation, Traditional");
            EcoMap.Add("B99", "Sicilian Defense, Najdorf Variation, Main Line");
            EcoMap.Add("C00", "French Defense");
            EcoMap.Add("C01", "French Defense, Exchange Variation");
            EcoMap.Add("C02", "French Defense, Advance Variation");
            EcoMap.Add("C03", "French Defense, Tarrasch Variation");
            EcoMap.Add("C04", "French Defense, Tarrasch, Guimard Variation");
            EcoMap.Add("C05", "French Defense, Tarrasch, Closed Variation");
            EcoMap.Add("C06", "French Defense, Tarrasch, Closed Variation");
            EcoMap.Add("C07", "French Defense, Tarrasch, Open Variation");
            EcoMap.Add("C08", "French Defense, Tarrasch, Open, 4.ed ed");
            EcoMap.Add("C09", "French Defense, Tarrasch, Open Variation");
            EcoMap.Add("C10", "French Defense, Paulsen Variation");
            EcoMap.Add("C11", "French Defense, Classical Variation");
            EcoMap.Add("C12", "French Defense, MacCutcheon Variation");
            EcoMap.Add("C13", "French Defense, Classical Variation");
            EcoMap.Add("C14", "French Defense, Classical Variation");
            EcoMap.Add("C15", "French Defense, Winawer Variation");
            EcoMap.Add("C16", "French Defense, Winawer Variation");
            EcoMap.Add("C17", "French Defense, Winawer Variation");
            EcoMap.Add("C18", "French Defense, Winawer Variation");
            EcoMap.Add("C19", "French Defense, Winawer Variation");
            EcoMap.Add("C20", "King's Pawn Game");
            EcoMap.Add("C21", "Center Game");
            EcoMap.Add("C22", "Center Game, Kieseritsky Variation");
            EcoMap.Add("C23", "Bishop's Opening");
            EcoMap.Add("C24", "Bishop's Opening");
            EcoMap.Add("C25", "Vienna Game");
            EcoMap.Add("C26", "Vienna Game");
            EcoMap.Add("C27", "Vienna Game, Stanley Variation");
            EcoMap.Add("C28", "Vienna Game, Falkbeer Variation");
            EcoMap.Add("C29", "Vienna Gambit");
            EcoMap.Add("C30", "King's Gambit");
            EcoMap.Add("C31", "King's Gambit Declined, Falkbeer Counter Gambit");
            EcoMap.Add("C32", "King's Gambit Declined, Falkbeer Counter Gambit");
            EcoMap.Add("C33", "King's Gambit Accepted");
            EcoMap.Add("C34", "King's Gambit Accepted, Fischer Defense");
            EcoMap.Add("C35", "King's Gambit Accepted, Cunningham Defense");
            EcoMap.Add("C36", "King's Gambit Accepted, Abbazia Defense");
            EcoMap.Add("C37", "King's Gambit Accepted");
            EcoMap.Add("C38", "King's Gambit Accepted, Greco Gambit");
            EcoMap.Add("C39", "King's Gambit Accepted, Allgaier Gambit");
            EcoMap.Add("C40", "King's Knight Opening");
            EcoMap.Add("C41", "Philidor Defense");
            EcoMap.Add("C42", "Petrov Defense");
            EcoMap.Add("C43", "Petrov Defense, Modern Attack");
            EcoMap.Add("C44", "King's Pawn Game, Konstantinopolsky Opening");
            EcoMap.Add("C45", "Scotch Game");
            EcoMap.Add("C46", "Three Knights Game");
            EcoMap.Add("C47", "Four Knights Game");
            EcoMap.Add("C48", "Four Knights Game, Spanish Variation");
            EcoMap.Add("C49", "Four Knights Game, Double Ruy Lopez");
            EcoMap.Add("C50", "Giuoco Piano");
            EcoMap.Add("C51", "Evans Gambit");
            EcoMap.Add("C52", "Evans Gambit, Main Line");
            EcoMap.Add("C53", "Giuoco Piano");
            EcoMap.Add("C54", "Giuoco Piano");
            EcoMap.Add("C55", "Two Knights Defense");
            EcoMap.Add("C56", "Two Knights Defense, 4.Ng5");
            EcoMap.Add("C57", "Two Knights Defense, Fritz Variation");
            EcoMap.Add("C58", "Two Knights Defense, Open Variation");
            EcoMap.Add("C59", "Two Knights Defense, Polerio Variation");
            EcoMap.Add("C60", "Ruy Lopez");
            EcoMap.Add("C61", "Ruy Lopez, Bird's Defense");
            EcoMap.Add("C62", "Ruy Lopez, Old Steinitz Defense");
            EcoMap.Add("C63", "Ruy Lopez, Schliemann Defense");
            EcoMap.Add("C64", "Ruy Lopez, Classical Variation");
            EcoMap.Add("C65", "Ruy Lopez, Berlin Defense");
            EcoMap.Add("C66", "Ruy Lopez");
            EcoMap.Add("C67", "Ruy Lopez, Berlin Defense");
            EcoMap.Add("C68", "Ruy Lopez, Exchange Variation");
            EcoMap.Add("C69", "Ruy Lopez, Exchange Variation, Gligoric Variation");
            EcoMap.Add("C70", "Ruy Lopez");
            EcoMap.Add("C71", "Ruy Lopez, Modern Steinitz Defense");
            EcoMap.Add("C72", "Ruy Lopez, Modern Steinitz Defense");
            EcoMap.Add("C73", "Ruy Lopez, Modern Steinitz Defense");
            EcoMap.Add("C74", "Ruy Lopez, Modern Steinitz Defense");
            EcoMap.Add("C75", "Ruy Lopez, Modern Steinitz Defense");
            EcoMap.Add("C76", "Ruy Lopez, Modern Steinitz Defense");
            EcoMap.Add("C77", "Ruy Lopez, Morphy Defense");
            EcoMap.Add("C78", "Ruy Lopez, Breyer Variation");
            EcoMap.Add("C79", "Ruy Lopez, Steinitz Defense Deferred");
            EcoMap.Add("C80", "Ruy Lopez, Open");
            EcoMap.Add("C81", "Ruy Lopez, Open, Howell Attack");
            EcoMap.Add("C82", "Ruy Lopez, Open, 9.h3");
            EcoMap.Add("C83", "Ruy Lopez, Open");
            EcoMap.Add("C84", "Ruy Lopez, Closed");
            EcoMap.Add("C85", "Ruy Lopez, Exchange Variation Doubly Deferred EcoMap.Add(DERLD);");
            EcoMap.Add("C86", "Ruy Lopez, Worrall Attack");
            EcoMap.Add("C87", "Ruy Lopez, Closed");
            EcoMap.Add("C88", "Ruy Lopez, Closed");
            EcoMap.Add("C89", "Ruy Lopez, Marshall Counterattack");
            EcoMap.Add("C90", "Ruy Lopez, Closed");
            EcoMap.Add("C91", "Ruy Lopez, Closed");
            EcoMap.Add("C92", "Ruy Lopez, Closed");
            EcoMap.Add("C93", "Ruy Lopez, Closed, Smyslov Defense");
            EcoMap.Add("C94", "Ruy Lopez, Closed, Breyer Defense");
            EcoMap.Add("C95", "Ruy Lopez, Closed, Breyer Defense, 9.h3");
            EcoMap.Add("C96", "Ruy Lopez, Closed");
            EcoMap.Add("C97", "Ruy Lopez, Closed, Chigorin");
            EcoMap.Add("C98", "Ruy Lopez, Closed, Chigorin, Yugoslav System");
            EcoMap.Add("C99", "Ruy Lopez, Closed, Chigorin, 12...cd");
            EcoMap.Add("D00", "Queen's Pawn Game");
            EcoMap.Add("D01", "Richter-Veresov Attack");
            EcoMap.Add("D02", "Queen's Pawn Game");
            EcoMap.Add("D03", "Torre Attack EcoMap.Add(Tartakower Variation);");
            EcoMap.Add("D04", "Queen's Pawn Game, Colle System");
            EcoMap.Add("D05", "Queen's Pawn Game, Rubinstein Opening");
            EcoMap.Add("D06", "Queen's Gambit Declined");
            EcoMap.Add("D07", "Queen's Gambit Declined, Chigorin Defense");
            EcoMap.Add("D08", "Queen's Gambit Declined, Albin Counter Gambit");
            EcoMap.Add("D09", "Queen's Gambit Declined, Albin Counter Gambit, 5.g3");
            EcoMap.Add("D10", "Queen's Gambit Declined Slav Defense");
            EcoMap.Add("D11", "Queen's Gambit Declined Slav Defense, 3.Nf3");
            EcoMap.Add("D12", "Queen's Gambit Declined Slav Defense, 4.e3");
            EcoMap.Add("D13", "Queen's Gambit Declined Slav Defense, Exchange Variation");
            EcoMap.Add("D14", "Queen's Gambit Declined Slav Defense, Exchange Variation");
            EcoMap.Add("D15", "Queen's Gambit Declined Slav Defense, 4.e3");
            EcoMap.Add("D16", "Queen's Gambit Declined Slav Defense");
            EcoMap.Add("D17", "Queen's Gambit Declined Slav Defense, Czech Variation");
            EcoMap.Add("D18", "Queen's Gambit Declined Slav Defense, Dutch Variation");
            EcoMap.Add("D19", "Queen's Gambit Declined Slav Defense, Dutch Variation");
            EcoMap.Add("D20", "Queen's Gambit Accepted");
            EcoMap.Add("D21", "Queen's Gambit Accepted");
            EcoMap.Add("D22", "Queen's Gambit Accepted");
            EcoMap.Add("D23", "Queen's Gambit Accepted");
            EcoMap.Add("D24", "Queen's Gambit Accepted");
            EcoMap.Add("D25", "Queen's Gambit Accepted");
            EcoMap.Add("D26", "Queen's Gambit Accepted");
            EcoMap.Add("D27", "Queen's Gambit Accepted, Classical Variation");
            EcoMap.Add("D28", "Queen's Gambit Accepted, Classical Variation");
            EcoMap.Add("D29", "Queen's Gambit Accepted, Classical Variation");
            EcoMap.Add("D30", "Queen's Gambit Declined");
            EcoMap.Add("D31", "Queen's Gambit Declined");
            EcoMap.Add("D32", "Queen's Gambit Declined, Tarrasch Defense");
            EcoMap.Add("D33", "Queen's Gambit Declined, Tarrasch Defense");
            EcoMap.Add("D34", "Queen's Gambit Declined, Tarrasch Defense");
            EcoMap.Add("D35", "Queen's Gambit Declined, Exchange Variation");
            EcoMap.Add("D36", "Queen's Gambit Declined, Exchange Variation");
            EcoMap.Add("D37", "Queen's Gambit Declined");
            EcoMap.Add("D38", "Queen's Gambit Declined, Ragozin Variation");
            EcoMap.Add("D39", "Queen's Gambit Declined, Ragozin Variation");
            EcoMap.Add("D40", "Queen's Gambit Declined, Semi-Tarrasch Defense");
            EcoMap.Add("D41", "Queen's Gambit Declined, Semi-Tarrasch Defense");
            EcoMap.Add("D42", "Queen's Gambit Declined, Semi-Tarrasch Defense");
            EcoMap.Add("D43", "Queen's Gambit Declined Semi-Slav");
            EcoMap.Add("D44", "Queen's Gambit Declined Semi-Slav");
            EcoMap.Add("D45", "Queen's Gambit Declined Semi-Slav");
            EcoMap.Add("D46", "Queen's Gambit Declined Semi-Slav");
            EcoMap.Add("D47", "Queen's Gambit Declined Semi-Slav");
            EcoMap.Add("D48", "Queen's Gambit Declined Semi-Slav, Meran Variation");
            EcoMap.Add("D49", "Queen's Gambit Declined Semi-Slav, Meran Variation");
            EcoMap.Add("D50", "Queen's Gambit Declined");
            EcoMap.Add("D51", "Queen's Gambit Declined");
            EcoMap.Add("D52", "Queen's Gambit Declined");
            EcoMap.Add("D53", "Queen's Gambit Declined");
            EcoMap.Add("D54", "Queen's Gambit Declined, Anti-Neo-Orthodox Variation");
            EcoMap.Add("D55", "Queen's Gambit Declined");
            EcoMap.Add("D56", "Queen's Gambit Declined");
            EcoMap.Add("D57", "Queen's Gambit Declined, Lasker Defense");
            EcoMap.Add("D58", "Queen's Gambit Declined, Tartakower Defense");
            EcoMap.Add("D59", "Queen's Gambit Declined, Tartakower");
            EcoMap.Add("D60", "Queen's Gambit Declined, Orthodox Defense");
            EcoMap.Add("D61", "Queen's Gambit Declined, Orthodox Defense");
            EcoMap.Add("D62", "Queen's Gambit Declined, Orthodox Defense");
            EcoMap.Add("D63", "Queen's Gambit Declined, Orthodox Defense");
            EcoMap.Add("D64", "Queen's Gambit Declined, Orthodox Defense, Rubinstein Attack");
            EcoMap.Add("D65", "Queen's Gambit Declined, Orthodox Defense, Rubinstein Attack");
            EcoMap.Add("D66", "Queen's Gambit Declined, Orthodox Defense, Rubinstein Attack");
            EcoMap.Add("D67", "Queen's Gambit Declined, Orthodox Defense, Bd3 line");
            EcoMap.Add("D68", "Queen's Gambit Declined, Orthodox Defense, Classical Variation");
            EcoMap.Add("D69", "Queen's Gambit Declined, Orthodox Defense, Classical Variation");
            EcoMap.Add("D70", "Neo-Grunfeld Defense");
            EcoMap.Add("D71", "Neo-Grunfeld Defense");
            EcoMap.Add("D72", "Neo-Grunfeld Defense, 5.cd");
            EcoMap.Add("D73", "Neo-Grunfeld Defense, 5.Nf3");
            EcoMap.Add("D74", "Neo-Grunfeld Defense, 6.cd Nxd5, 7.O-O Nb6");
            EcoMap.Add("D75", "Neo-Grunfeld Defense, 6.cd Nxd5, 7.O-O Nb6");
            EcoMap.Add("D76", "Neo-Grunfeld Defense, 6.cd Nxd5, 7.O-O Nb6");
            EcoMap.Add("D77", "Neo-Grunfeld Defense, 6.O-O");
            EcoMap.Add("D78", "Neo-Grunfeld Defense, 6.O-O");
            EcoMap.Add("D79", "Neo-Grunfeld Defense, Ultra-Accelerated");
            EcoMap.Add("D80", "Grunfeld Defense");
            EcoMap.Add("D81", "Grunfeld Defense, Russian Variation");
            EcoMap.Add("D82", "Grunfeld Defense, 4.Bf4");
            EcoMap.Add("D83", "Grunfeld Defense, 4.Bf4");
            EcoMap.Add("D84", "Grunfeld Defense, 4.e3");
            EcoMap.Add("D85", "Grunfeld Defense, Exchange Variation");
            EcoMap.Add("D86", "Grunfeld Defense, Exchange Variation");
            EcoMap.Add("D87", "Grunfeld Defense, Exchange Variation");
            EcoMap.Add("D88", "Grunfeld Defense, Spassky Variation");
            EcoMap.Add("D89", "Grunfeld Defense, Spassky Variation");
            EcoMap.Add("D90", "Grunfeld Defense");
            EcoMap.Add("D91", "Grunfeld Defense");
            EcoMap.Add("D92", "Grunfeld Defense, 5.Bf4");
            EcoMap.Add("D93", "Grunfeld Defense, 5.Bf4");
            EcoMap.Add("D94", "Grunfeld Defense, 5.Bf4");
            EcoMap.Add("D95", "Grunfeld Defense, 5.Nf3");
            EcoMap.Add("D96", "Grunfeld Defense, Russian Variation");
            EcoMap.Add("D97", "Grunfeld Defense, Russian Variation");
            EcoMap.Add("D98", "Grunfeld Defense, Russian Variation");
            EcoMap.Add("D99", "Grunfeld Defense, Smyslov Variation");
            EcoMap.Add("E00", "Queen's Pawn Game");
            EcoMap.Add("E01", "Catalan, Closed");
            EcoMap.Add("E02", "Catalan, Open");
            EcoMap.Add("E03", "Catalan, Open");
            EcoMap.Add("E04", "Catalan, Open, 5.Nf3");
            EcoMap.Add("E05", "Catalan, Open, 6.Nf3");
            EcoMap.Add("E06", "Richter-Veresov Attack");
            EcoMap.Add("E07", "King's Indian Attack");
            EcoMap.Add("E08", "King's Indian Attack");
            EcoMap.Add("E09", "Catalan, Closed");
            EcoMap.Add("E10", "Queen's Pawn Game");
            EcoMap.Add("E11", "Bogo-Indian Defense");
            EcoMap.Add("E12", "Queen's Indian Defense");
            EcoMap.Add("E13", "Queen's Indian Defense, Petrosian Variation");
            EcoMap.Add("E14", "Queen's Indian Defense, 4.e3");
            EcoMap.Add("E15", "Queen's Indian Defense, Nimzowitsch Variation");
            EcoMap.Add("E16", "Queen's Indian Defense, Capablanca Variation");
            EcoMap.Add("E17", "Queen's Indian Defense, Classical Variation");
            EcoMap.Add("E18", "Queen's Indian Defense, Old Main Line, 7.Nc3");
            EcoMap.Add("E19", "Queen's Indian Defense, Old Main Line, 9.Qxc3");
            EcoMap.Add("E20", "Nimzo-Indian Defense");
            EcoMap.Add("E21", "Nimzo-Indian Defense");
            EcoMap.Add("E22", "Nimzo-Indian Defense, Spielmann Variation");
            EcoMap.Add("E23", "Nimzo-Indian Defense, Spielmann Variation");
            EcoMap.Add("E24", "Nimzo-Indian Defense, Saemisch Variation");
            EcoMap.Add("E25", "Nimzo-Indian Defense, Saemisch Variation");
            EcoMap.Add("E26", "Nimzo-Indian Defense, Saemisch Variation");
            EcoMap.Add("E27", "Nimzo-Indian Defense, Saemisch Variation, 5...a6");
            EcoMap.Add("E28", "Nimzo-Indian Defense, Saemisch Variation");
            EcoMap.Add("E29", "Nimzo-Indian Defense, Saemisch Variation");
            EcoMap.Add("E30", "Nimzo-Indian Defense");
            EcoMap.Add("E31", "Nimzo-Indian Defense, Leningrad Variation");
            EcoMap.Add("E32", "Nimzo-Indian Defense");
            EcoMap.Add("E33", "Nimzo-Indian Defense, Classical Variation");
            EcoMap.Add("E34", "Nimzo-Indian Defense, Classical Variation");
            EcoMap.Add("E35", "Nimzo-Indian Defense, Classical Variation");
            EcoMap.Add("E36", "Nimzo-Indian Defense, Classical Variation");
            EcoMap.Add("E37", "Nimzo-Indian Defense, Classical Variation");
            EcoMap.Add("E38", "Nimzo-Indian Defense, Classical Variation");
            EcoMap.Add("E39", "Nimzo-Indian Defense, Classical Variation");
            EcoMap.Add("E40", "Nimzo-Indian Defense");
            EcoMap.Add("E41", "Nimzo-Indian Defense");
            EcoMap.Add("E42", "Nimzo-Indian Defense, 4.e3 c5");
            EcoMap.Add("E43", "Nimzo-Indian Defense, Fischer Variation");
            EcoMap.Add("E44", "Nimzo-Indian Defense, Fischer Variation");
            EcoMap.Add("E45", "Nimzo-Indian Defense, 4.e3");
            EcoMap.Add("E46", "Nimzo-Indian Defense");
            EcoMap.Add("E47", "Nimzo-Indian Defense, 4.e3 O-O 5.Bd3");
            EcoMap.Add("E48", "Nimzo-Indian Defense, 4.e3 O-O 5.Bd3");
            EcoMap.Add("E49", "Nimzo-Indian Defense, 4.e3, Botvinnik System");
            EcoMap.Add("E50", "Nimzo-Indian Defense");
            EcoMap.Add("E51", "Nimzo-Indian Defense, 4.e3");
            EcoMap.Add("E52", "Nimzo-Indian Defense, 4.e3, Main line with ...b6");
            EcoMap.Add("E53", "Nimzo-Indian Defense, 4.e3, Main line with ...b6");
            EcoMap.Add("E54", "Nimzo-Indian Defense, Gligoric System, Smyslov Variation");
            EcoMap.Add("E55", "Nimzo-Indian Defense, Gligoric System, Bronstein Variation");
            EcoMap.Add("E56", "Nimzo-Indian Defense, 4.e3, Main line with 7...Nc6");
            EcoMap.Add("E57", "Nimzo-Indian Defense, 4.e3, Main line with 8...d5");
            EcoMap.Add("E58", "Nimzo-Indian Defense, 4.e3, Main line with 8...Bxc3");
            EcoMap.Add("E59", "Nimzo-Indian Defense, 4.e3, Main line");
            EcoMap.Add("E60", "King's Indian Defense");
            EcoMap.Add("E61", "King's Indian Defense");
            EcoMap.Add("E62", "King's Indian Defense, Fianchetto Variation");
            EcoMap.Add("E63", "King's Indian Defense, Fianchetto Variation");
            EcoMap.Add("E64", "King's Indian Defense, Fianchetto Variation");
            EcoMap.Add("E65", "King's Indian Defense, Fianchetto Variation");
            EcoMap.Add("E66", "King's Indian Defense, Fianchetto Variation, Yugoslav System");
            EcoMap.Add("E67", "King's Indian Defense, Fianchetto Variation");
            EcoMap.Add("E68", "King's Indian Defense, Fianchetto Variation, Classical Variation");
            EcoMap.Add("E69", "King's Indian Defense, Fianchetto Variation, Classical Main Line");
            EcoMap.Add("E70", "King's Indian Defense");
            EcoMap.Add("E71", "King's Indian Defense, Makagonov Variation");
            EcoMap.Add("E72", "King's Indian Defense, Normal Variation");
            EcoMap.Add("E73", "King's Indian Defense, Normal Variation");
            EcoMap.Add("E74", "King's Indian Defense, Averbakh Variation");
            EcoMap.Add("E75", "King's Indian Defense, Averbakh Variation");
            EcoMap.Add("E76", "King's Indian Defense, Four Pawns Attack");
            EcoMap.Add("E77", "King's Indian Defense, Four Pawns Attack");
            EcoMap.Add("E78", "King's Indian Defense, Four Pawns Attack, with Be2 and Nf3");
            EcoMap.Add("E79", "King's Indian Defense, Four Pawns Attack, Main line");
            EcoMap.Add("E80", "King's Indian Defense, Sämisch Variation");
            EcoMap.Add("E81", "King's Indian Defense, Sämisch Variation");
            EcoMap.Add("E82", "King's Indian Defense, Sämisch Variation");
            EcoMap.Add("E83", "King's Indian Defense, Sämisch Variation");
            EcoMap.Add("E84", "King's Indian Defense, Sämisch Variation, Panno Main line");
            EcoMap.Add("E85", "King's Indian Defense, Sämisch Variation, Orthodox Variation");
            EcoMap.Add("E86", "King's Indian Defense, Sämisch Variation, Orthodox Variation, 7.Nge2");
            EcoMap.Add("E87", "King's Indian Defense, Sämisch Variation, Orthodox Variation");
            EcoMap.Add("E88", "King's Indian Defense, Sämisch Variation, Orthodox Variation, 7.d5");
            EcoMap.Add("E89", "King's Indian Defense, Sämisch Variation, Orthodox Variation, 7...Nbd7");
            EcoMap.Add("E90", "King's Indian Defense");
            EcoMap.Add("E91", "King's Indian Defense");
            EcoMap.Add("E92", "King's Indian Defense");
            EcoMap.Add("E93", "King's Indian Defense, Petrosian System");
            EcoMap.Add("E94", "King's Indian Defense, Orthodox Variation");
            EcoMap.Add("E95", "King's Indian Defense, Orthodox Variation");
            EcoMap.Add("E96", "King's Indian Defense, Orthodox Variation, 7.Nbd2");
            EcoMap.Add("E97", "King's Indian Defense, Orthodox Variation, Aronin-Taimanov Variation");
            EcoMap.Add("E98", "King's Indian Defense, Orthodox Variation, Aronin-Taimanov Variation");
            EcoMap.Add("E99", "King's Indian Defense, Orthodox Variation, Taimanov Variation");


            return EcoMap;
        }

        int FindPlayer(int pid)
        {
            var url = "https://www.chessgames.com/perl/chessplayer?pid="+pid;

            HtmlWeb web = new HtmlWeb();
            HtmlDocument doc = web.Load(url);
            string findyears = "Years covered:";
            string elo = "Last FIDE rating:";
            string htmlCode = doc.DocumentNode.OuterHtml;
            int yearspos = htmlCode.IndexOf(findyears) + 14;
            while (htmlCode[yearspos] != '>') {
                yearspos++;
            }
            yearspos++;
            findyears = "";
            while (htmlCode[yearspos] != '<')
            {
                findyears += htmlCode[yearspos];
                yearspos++;
            }

            int elopos = htmlCode.IndexOf(elo) + 17;
            while (htmlCode[elopos] != '>')
            {
                elopos++;
            }
            elopos++;
            elo = "";
            while (htmlCode[elopos] != '<')
            {
                elo += htmlCode[elopos];
                elopos++;
            }


            string name = "size=\"+3\"";
            int namepos = htmlCode.IndexOf(name) + 11;

            while (htmlCode[namepos] != '>')
            {
                namepos++;
            }
            namepos++;
            name = "";
            while (htmlCode[namepos] != '<')
            {
                name += htmlCode[namepos];
                namepos++;
            }

            GlobalList.elo = Int32.Parse(elo);
            GlobalList.name = name;
            string from="";
            int i = 0;
            while (findyears[i]!=' ') { 
                from+= findyears[i];
                i++;
            }
            i+=4;
            GlobalList.startYear = Int32.Parse(from);
            findyears = findyears.Substring(i, findyears.Length-i);
            GlobalList.lastYear = Int32.Parse(findyears);
            return 1;
        }

        [HttpGet]
        [Route("/GetData")]
        public IActionResult GetName()
        {
            return Ok(new{GlobalList.name , GlobalList.elo  , GlobalList.startYear, GlobalList.lastYear });
        }

        [HttpGet]
        [Route("/NewFilters")]
        public IActionResult NewFilters()
        {
            String color = Request.Query["color"].ToString();

            if (Request.Query["lastyear"].ToString() == "" ) {
                return BadRequest();
            }
            if (Request.Query["startyear"].ToString() == "")
            {
                return BadRequest();
            }

            int lastyear = Int32.Parse(Request.Query["lastyear"].ToString());
            int startyear = Int32.Parse(Request.Query["startyear"].ToString());

            List<GameDetails> games = GamesByColor(color, GlobalList.name);
            games = games.Where(n => n.year >= startyear && n.year <= lastyear).OrderBy(o => o.year).ToList();
            string jsonusedgames = JsonConvert.SerializeObject(games);
            _cache.Set("usedgames"+GlobalList.Pid.ToString(), jsonusedgames);
            string json = JsonConvert.SerializeObject(games);
            return Ok(json);
        }


        [HttpGet]
        [Route("/CalculateNewFiltersByName")]
        public async Task<IActionResult> CalculateByNameFilter()
        {
            string json = "";
            string jsonusedgames = (string)_cache.Get("usedgames"+GlobalList.Pid.ToString());
            List<GameDetails> UseGames = JsonConvert.DeserializeObject<List<GameDetails>>(jsonusedgames);

            if (UseGames.Count == 0)
            {
                Console.WriteLine("In");
                return Content(json, "application/json");
            }
            else {
                Console.WriteLine(UseGames.Count+" UsedGames");

            }
            Console.WriteLine(UseGames.Count+"foo");
            Dictionary<string, string> ECOMAP = init_ECO_MAP();
            Dictionary<string, int> ECOCount = new Dictionary<string, int>();
            Dictionary<string, int> WinRates = new Dictionary<string, int>();
            int total_games = UseGames.Count;
            foreach (string key in ECOMAP.Keys)
            {
                ECOCount.Add(key, 0);
                WinRates.Add(key, 0);

            }

            foreach (GameDetails g in UseGames)
            {
                ECOCount[g.ECO]++;
                Console.WriteLine(ECOCount[g.ECO]);
            }

            foreach (GameDetails g in UseGames)
            {
                if (g.ECO != "000")
                {
                    if (WinRate(g, GlobalList.name))
                    {
                        WinRates[g.ECO]++;
                    }
                }
            }

            var SortEcoCount = ECOCount.OrderByDescending(e => e.Value).ToList();

            List<DataOpeningName> DataOpening = new List<DataOpeningName>();
            foreach (var item in SortEcoCount)
            {
                Console.WriteLine(item.Key + ": " + ECOCount[item.Key]);
                if (ECOCount[item.Key] != 0)
                {
                    double prate = ((double)(ECOCount[item.Key]) / (double)(total_games)) * 100;
                    double wrate = ((double)(WinRates[item.Key]) / (double)(ECOCount[item.Key])) * 100;
                    DataOpening.Add(new DataOpeningName(item.Key, ECOMAP[item.Key], Math.Round(prate, 1), Math.Round(wrate, 1)));
                }
            }
            Console.WriteLine(DataOpening.Count+" DataOpening");
            json = JsonConvert.SerializeObject(DataOpening);
            return Content(json, "application/json");
        }

        [HttpGet]
        [Route("OpenProfile")]
        public IActionResult OpenProfile()
        {
            Console.WriteLine("OpenProfile");

            int pid1 = Int32.Parse(Request.Query["pid"].ToString());

            SqlConnection con = new SqlConnection("Server=DESKTOP-DKKS7HR; Database=ChessScoutDB;Trusted_Connection=True; Encrypt=False");
            SqlDataAdapter da = new SqlDataAdapter("SELECT * FROM ScoutProfiles WHERE Pid= " + pid1 + ";", con);
            DataTable dt = new DataTable();

            da.Fill(dt);
            var sp = new List<ScoutData>();
            Console.WriteLine(dt.Rows.Count);
            int i;
            if (dt.Rows.Count > 0)
            {
                for (i = 0; i < dt.Rows.Count; i++)
                {
                    ScoutData profile = new ScoutData();
                    profile.PlayerName = Convert.ToString(dt.Rows[i]["Playername"]);
                    profile.Elo = Convert.ToInt32(dt.Rows[i]["Elo"]);
                    profile.Uid = Convert.ToInt32(dt.Rows[i]["Uid"]);
                    profile.Pid = Convert.ToInt32(dt.Rows[i]["Pid"]);
                    profile.games = Convert.ToString(dt.Rows[i]["JsonGames"]);
                    profile.opening_tree_data = Convert.ToString(dt.Rows[i]["JsonOpeningTree"]);
                    profile.preferted_openings_data = Convert.ToString(dt.Rows[i]["JsonOpeningPreferted"]);

                    profile.UserName = "";

                    sp.Add(profile);




                }
                Response.StatusCode = 200;
            }
            else
            {
                Response.StatusCode = 404;

            }
            ScoutData temp = sp[0];

            GlobalList.name = temp.PlayerName;
            string[] words = temp.PlayerName.Split(' ');


            var url = "https://www.chessgames.com/perl/ezsearch.pl?search=" + words[0] + "+" + words[1];

            HtmlWeb web = new HtmlWeb();
            HtmlDocument doc = web.Load(url);
            string page = doc.DocumentNode.OuterHtml;


            /*=====Search for pid=====*/
            string subStr = "pid=";
            int pos = page.IndexOf(subStr) + 4;
            if (pos == -1)
            {

            }
            i = 0;
            string pid = "";
            while (page[pos + i] != '\"')
            {
                pid += page[pos + i++];

            }

            int num_pid = Int32.Parse(pid);
            GlobalList.Pid = num_pid;
            _cache.Set("games" + GlobalList.Pid.ToString(), temp.games);
            _cache.Set("usedgames" + GlobalList.Pid.ToString(), temp.games);

            String json = JsonConvert.SerializeObject(sp);
            return Content(json, "application/json");

        }


    }
}
