using System.Xml;


namespace ChessScout.Models
{
    [Serializable]
    public class GameDetails
    {
        public GameDetails(int Gid,string White,string Black, string result, int num_moves,int year,string eco ,string tour) { 
            this.Gid = Gid;
            this.White_Player = White;
            this.Black_Player = Black;
            this.result = result;
            this.num_moves = num_moves;
            this.year = year;
            this.ECO = eco;
            this.tour = tour;
            this.Game = null;
            movelist = new List<string> ();
        }
        public GameDetails() { this.Game = null; }
        public List <string> movelist;
        public string White_Player;
        public string Black_Player;

        public int Gid;
        public int num_moves;
        public string ECO;
        public string result;
        public int year;
        public int month;
        public int day;
        public string tour;
        public string Game;
        public void addGamePgn(string Game)
        {
            this.Game = Game;
        }

        public void print_info()
        {
            Console.WriteLine("Gid : "+Gid+", Moves : "+num_moves+ ", Result : " + result + ", Eco : " + ECO + ", Tour : " + tour + ", Year : " + year + ", White : " + White_Player + ", Black : " + Black_Player);
        } 
        
    }
}
