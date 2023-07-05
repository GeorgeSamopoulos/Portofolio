using Microsoft.AspNetCore.Mvc;
using System.Data;
using ChessScout.Models;
using Microsoft.Data.SqlClient;
using Newtonsoft.Json;
using System.Web;
using Microsoft.AspNetCore.Http;
using Azure.Core;
using Azure;
using Microsoft.EntityFrameworkCore.Migrations.Operations;
using System.Web.Helpers;
using System.Runtime.Intrinsics.X86;
using static Microsoft.EntityFrameworkCore.DbLoggerCategory;
using NuGet.Protocol.Plugins;

namespace ChessScout.Controllers
{
    [ApiController]
    [Route("api/[controller]")]
    public class UserController : ControllerBase
    {

        private readonly ChessScoutDbContext _dbcontext;
        public UserController(ChessScoutDbContext _context)
        {
            _dbcontext = _context;
        }

        [HttpGet]
        [Route("SignIn")]
        public IActionResult GetUsers()
        {

            String password = Request.Query["password"].ToString();
            String username = Request.Query["username"].ToString();
            Console.WriteLine(username);
            Console.WriteLine(password);

            SqlConnection con = new SqlConnection("Server=DESKTOP-DKKS7HR; Database=ChessScoutDB;Trusted_Connection=True; Encrypt=False");
            SqlDataAdapter da = new SqlDataAdapter("SELECT * FROM Users WHERE username= '" + username + "' AND pass = '" + password + "' ;", con);
            DataTable dt = new DataTable();
            da.Fill(dt);
            var resp = new List<User>();
            string json = "";
            if (dt.Rows.Count > 0)
            {
                for (int i = 0; i < dt.Rows.Count; i++)
                {
                    User user = new User();
                    user.Uid = Convert.ToInt32(dt.Rows[0]["uid"]);
                    user.Email = Convert.ToString(dt.Rows[0]["email"]);
                    user.Username = Convert.ToString(dt.Rows[0]["username"]);
                    user.Pass = Convert.ToString(dt.Rows[0]["pass"]);
                    user.Country = Convert.ToString(dt.Rows[0]["country"]);
                    user.Birthday = Convert.ToDateTime(dt.Rows[0]["birthday"]);

                    resp.Add(user);
                }
                Response.StatusCode = 200;
            }
            else
            {
                Response.StatusCode = 404;

            }
            json = JsonConvert.SerializeObject(resp);
            return Content(json, "application/json");
        }


        [HttpPost]
        [Route("SignUp")]
        public IActionResult PostSignUp([FromBody] User user)
        {
            if (user.Username == null || user.Email == null)
            {
                return BadRequest(new { message = "null varables" });
            }
            Console.WriteLine("SignUp");
            if (!CheckDuplication(user.Username, user.Email))
            {
                Response.StatusCode = 402;
                return BadRequest(new { message = "Username or Email Duplication" });
            }
            int uid = 1;
            try
            {
                SqlConnection con = new SqlConnection("Server=DESKTOP-DKKS7HR; Database=ChessScoutDB;Trusted_Connection=True; Encrypt=False");
                SqlDataAdapter da = new SqlDataAdapter("SELECT MAX(uid) FROM Users", con);
                DataTable dt = new DataTable();
                da.Fill(dt);
                if (dt.Rows.Count > 0)
                {
                    uid = Convert.ToInt32(dt.Rows[0][0]);

                }

            }
            catch (Exception ex)
            {
                Response.StatusCode = 403;
                return BadRequest(new { message = ex.Message });
            }

            try
            {
                SqlConnection con = new SqlConnection("Server=DESKTOP-DKKS7HR; Database=ChessScoutDB;Trusted_Connection=True; Encrypt=False");
                String query = "INSERT INTO Users VALUES (@uid,@username,@pass,@email,@country,@birthday)";
                SqlCommand cmd = new SqlCommand(query, con);

                cmd.Parameters.Add(new SqlParameter("@uid", ++uid));
                cmd.Parameters.Add(new SqlParameter("@username", user.Username));
                cmd.Parameters.Add(new SqlParameter("@pass", user.Pass));
                cmd.Parameters.Add(new SqlParameter("@country", user.Country));
                cmd.Parameters.Add(new SqlParameter("@email", user.Email));
                cmd.Parameters.Add(new SqlParameter("@birthday", user.Birthday));


                con.Open();
                int ret = cmd.ExecuteNonQuery();
                con.Close();
                Response.StatusCode = 200;
                return Ok(new { message = "User inserted successfully" }); ;
            }
            catch (Exception ex)
            {
                Response.StatusCode = 403;
                return BadRequest(new { message = ex.Message });
            }
        }

        [HttpGet]
        public bool CheckDuplication(string username, string email)
        {
            Console.WriteLine("CheckSignUp");

            SqlConnection con = new SqlConnection("Server=DESKTOP-DKKS7HR; Database=ChessScoutDB;Trusted_Connection=True; Encrypt=False");
            SqlDataAdapter da = new SqlDataAdapter("SELECT * FROM Users WHERE username= '" + username + "' OR email = '" + email + "' ;", con);
            DataTable dt = new DataTable();
            da.Fill(dt);
            if (dt.Rows.Count > 0)
            {
                return false;

            }

            return true;

        }

        [HttpPost]
        [Route("SaveProfile")]
        public IActionResult SaveProfile([FromBody] ScoutData sc)
        {
            Console.WriteLine("SaveProfile");


            Console.WriteLine(sc.UserName);
            String name = sc.UserName;


            SqlConnection con = new SqlConnection("Server=DESKTOP-DKKS7HR; Database=ChessScoutDB;Trusted_Connection=True; Encrypt=False");
            SqlDataAdapter da = new SqlDataAdapter("SELECT * FROM Users WHERE username= '" + name + "' ;", con);
            DataTable dt = new DataTable();
            da.Fill(dt);
            var resp = new List<User>();
            string json = "";
            if (dt.Rows.Count > 0)
            {
                for (int i = 0; i < dt.Rows.Count; i++)
                {
                    User user = new User();
                    user.Uid = Convert.ToInt32(dt.Rows[i]["uid"]);
                    user.Email = Convert.ToString(dt.Rows[i]["email"]);
                    user.Username = Convert.ToString(dt.Rows[i]["username"]);
                    user.Pass = Convert.ToString(dt.Rows[i]["pass"]);
                    user.Country = Convert.ToString(dt.Rows[i]["country"]);
                    user.Birthday = Convert.ToDateTime(dt.Rows[i]["birthday"]);

                    resp.Add(user);
                }
                Response.StatusCode = 200;
            }
            else
            {
                Response.StatusCode = 404;

            }

            int uid = (int)resp[0].Uid;


            con = new SqlConnection("Server=DESKTOP-DKKS7HR; Database=ChessScoutDB;Trusted_Connection=True; Encrypt=False");
            da = new SqlDataAdapter("SELECT Pid FROM ScoutProfiles ", con);
            dt = new DataTable();
            da.Fill(dt);
            int pid = dt.Rows.Count;


            con = new SqlConnection("Server=DESKTOP-DKKS7HR; Database=ChessScoutDB;Trusted_Connection=True; Encrypt=False");
            String query = "INSERT INTO ScoutProfiles VALUES (@pid,@uid,@name,@elo,@games,@opening_preferted,@opening_tree)";
            SqlCommand cmd = new SqlCommand(query, con);

            cmd.Parameters.Add(new SqlParameter("@pid", pid));
            cmd.Parameters.Add(new SqlParameter("@uid", uid));
            cmd.Parameters.Add(new SqlParameter("@name", sc.PlayerName));
            cmd.Parameters.Add(new SqlParameter("@elo", sc.Elo));
            cmd.Parameters.Add(new SqlParameter("@opening_preferted", sc.preferted_openings_data));
            cmd.Parameters.Add(new SqlParameter("@games", sc.games));
            cmd.Parameters.Add(new SqlParameter("@opening_tree", sc.opening_tree_data));
            con.Open();
            int ret = cmd.ExecuteNonQuery();
            con.Close();

            json = "";
            return Content(json, "application/json");

        }

        [HttpGet]
        [Route("GetProfiles")]
        public IActionResult GetProfiles()
        {
            Console.WriteLine("GetProfiles");

            String username = Request.Query["username"].ToString();
            String password = Request.Query["password"].ToString();
            SqlConnection con = new SqlConnection("Server=DESKTOP-DKKS7HR; Database=ChessScoutDB;Trusted_Connection=True; Encrypt=False");
            SqlDataAdapter da = new SqlDataAdapter("SELECT * FROM Users WHERE username= '" + username + "' AND pass = '" + password + "'" + ";", con);
            DataTable dt = new DataTable();
            da.Fill(dt);
            var resp = new List<User>();
            string json = "";
            if (dt.Rows.Count > 0)
            {

                for (int i = 0; i < dt.Rows.Count; i++)
                {
                    User user = new User();
                    user.Uid = Convert.ToInt32(dt.Rows[i]["uid"]);
                    user.Email = Convert.ToString(dt.Rows[i]["email"]);
                    user.Username = Convert.ToString(dt.Rows[i]["username"]);
                    user.Pass = Convert.ToString(dt.Rows[i]["pass"]);
                    user.Country = Convert.ToString(dt.Rows[i]["country"]);
                    user.Birthday = Convert.ToDateTime(dt.Rows[i]["birthday"]);

                    resp.Add(user);
                }
                Response.StatusCode = 200;
            }
            else
            {
                Response.StatusCode = 404;

            }
            int uid = (int)resp[0].Uid;

            con = new SqlConnection("Server=DESKTOP-DKKS7HR; Database=ChessScoutDB;Trusted_Connection=True; Encrypt=False");
            da = new SqlDataAdapter("SELECT * FROM ScoutProfiles WHERE Uid=" + uid + " ;", con);
            dt = new DataTable();
            da.Fill(dt);
            var sp = new List<ScoutData>();

            if (dt.Rows.Count > 0)
            {
                for (int i = 0; i < dt.Rows.Count; i++)
                {
                    ScoutData profile = new ScoutData();
                    profile.PlayerName = Convert.ToString(dt.Rows[i]["Playername"]);
                    profile.Elo = Convert.ToInt32(dt.Rows[i]["Elo"]);
                    profile.Uid = Convert.ToInt32(dt.Rows[i]["Uid"]);
                    profile.Pid = Convert.ToInt32(dt.Rows[i]["Pid"]);

                    profile.UserName = "";

                    sp.Add(profile);




                }
                Response.StatusCode = 200;
            }
            else
            {
                Response.StatusCode = 404;

            }


            json = JsonConvert.SerializeObject(sp);
            return Content(json, "application/json");

        }


        [HttpGet]
        [Route("DeleteProfiles")]
        public IActionResult DeleteProfiles()
        {
            Console.WriteLine("DeleteProfile");

            String pid = Request.Query["pid"].ToString();
            int Pid = Convert.ToInt32(pid);

            SqlConnection con = new SqlConnection("Server=DESKTOP-DKKS7HR; Database=ChessScoutDB;Trusted_Connection=True; Encrypt=False");
            String query = "DELETE FROM ScoutProfiles WHERE Pid=" + Pid + ";";
            SqlCommand cmd = new SqlCommand(query, con);
            con.Open();
            int ret = cmd.ExecuteNonQuery();
            con.Close();
            Response.StatusCode = 200;
            String json = JsonConvert.SerializeObject("");
            return Content(json, "application/json");

        }

        
        [HttpGet]
        [Route("SaveGame")]
        public IActionResult SaveGame()
        {

            Console.WriteLine("SaveGame");

            String username = Request.Query["username"].ToString();
            String game = Request.Query["game"].ToString();
            String white = Request.Query["white"].ToString();
            String black = Request.Query["black"].ToString();
            String result = Request.Query["result"].ToString();


            SqlConnection con = new SqlConnection("Server=DESKTOP-DKKS7HR; Database=ChessScoutDB;Trusted_Connection=True; Encrypt=False");
            SqlDataAdapter da = new SqlDataAdapter("SELECT * FROM Users WHERE username= '" + username + "' ;", con);
            DataTable dt = new DataTable();
            da.Fill(dt);
            var resp = new List<User>();

            if (dt.Rows.Count > 0)
            {
                for (int i = 0; i < dt.Rows.Count; i++)
                {
                    User user = new User();
                    user.Uid = Convert.ToInt32(dt.Rows[i]["uid"]);
                    user.Email = Convert.ToString(dt.Rows[i]["email"]);
                    user.Username = Convert.ToString(dt.Rows[i]["username"]);
                    user.Pass = Convert.ToString(dt.Rows[i]["pass"]);
                    user.Country = Convert.ToString(dt.Rows[i]["country"]);
                    user.Birthday = Convert.ToDateTime(dt.Rows[i]["birthday"]);

                    resp.Add(user);
                }
                Response.StatusCode = 200;
            }
            else
            {
                Response.StatusCode = 404;

            }
            int uid = (int)resp[0].Uid;


            con = new SqlConnection("Server=DESKTOP-DKKS7HR; Database=ChessScoutDB;Trusted_Connection=True; Encrypt=False");
            da = new SqlDataAdapter("SELECT Gid FROM ChessGame;", con);
            dt = new DataTable();
            da.Fill(dt);

            int gid = dt.Rows.Count;
            Console.WriteLine(gid);
            con = new SqlConnection("Server=DESKTOP-DKKS7HR; Database=ChessScoutDB;Trusted_Connection=True; Encrypt=False");
            String query = "INSERT INTO ChessGame VALUES (@gid,@uid,@white,@black,@result,@game)";
            SqlCommand cmd = new SqlCommand(query, con);

            cmd.Parameters.Add(new SqlParameter("@gid", gid));
            cmd.Parameters.Add(new SqlParameter("@uid", uid));
            cmd.Parameters.Add(new SqlParameter("@white", white));
            cmd.Parameters.Add(new SqlParameter("@black", black));
            cmd.Parameters.Add(new SqlParameter("@result", result));
            cmd.Parameters.Add(new SqlParameter("@game", game));


            con.Open();
            int ret = cmd.ExecuteNonQuery();
            con.Close();


            String json = "";
            return Content(json, "application/json");
        }



        [HttpGet]
        [Route("GetGames")]
        public IActionResult GetGames()
        {

            Console.WriteLine("GetGames");

            String username = Request.Query["username"].ToString();
            SqlConnection con = new SqlConnection("Server=DESKTOP-DKKS7HR; Database=ChessScoutDB;Trusted_Connection=True; Encrypt=False");
            SqlDataAdapter da = new SqlDataAdapter("SELECT * FROM Users WHERE username= '" + username + "' ;", con);
            DataTable dt = new DataTable();
            da.Fill(dt);
            var resp = new List<User>();

            if (dt.Rows.Count > 0)
            {
                for (int i = 0; i < dt.Rows.Count; i++)
                {
                    User user = new User();
                    user.Uid = Convert.ToInt32(dt.Rows[i]["uid"]);
                    user.Email = Convert.ToString(dt.Rows[i]["email"]);
                    user.Username = Convert.ToString(dt.Rows[i]["username"]);
                    user.Pass = Convert.ToString(dt.Rows[i]["pass"]);
                    user.Country = Convert.ToString(dt.Rows[i]["country"]);
                    user.Birthday = Convert.ToDateTime(dt.Rows[i]["birthday"]);

                    resp.Add(user);
                }
                Response.StatusCode = 200;
            }
            else
            {
                Response.StatusCode = 404;

            }
            int uid = (int)resp[0].Uid;

            con = new SqlConnection("Server=DESKTOP-DKKS7HR; Database=ChessScoutDB;Trusted_Connection=True; Encrypt=False");
            da = new SqlDataAdapter("SELECT * FROM ChessGame WHERE Uid= " + uid + " ;", con);
            dt = new DataTable();
            da.Fill(dt);
            var games = new List<GameDetails>();
            GameDetails game;
            if (dt.Rows.Count > 0)
            {
                for (int i = 0; i < dt.Rows.Count; i++)
                {
                    game = new GameDetails();
                    game.Gid = Convert.ToInt32(dt.Rows[i]["Gid"]);
                    game.White_Player = Convert.ToString(dt.Rows[i]["WhitePlayer"]);
                    game.Black_Player = Convert.ToString(dt.Rows[i]["BlackPlayer"]);
                    game.result = Convert.ToString(dt.Rows[i]["Result"]);
                    game.Game = Convert.ToString(dt.Rows[i]["JsonGame"]);

                    games.Add(game);
                }
                Response.StatusCode = 200;
            }
            else
            {
                Response.StatusCode = 404;

            }



            String json = JsonConvert.SerializeObject(games);
            return Content(json, "application/json");
        }

        [HttpGet]
        [Route("DeleteGame")]
        public IActionResult DeleteGame()
        {

            Console.WriteLine("DeleteGame");
            String g = Request.Query["gid"].ToString();
            int gid = Convert.ToInt32(g);
            SqlConnection con = new SqlConnection("Server=DESKTOP-DKKS7HR; Database=ChessScoutDB;Trusted_Connection=True; Encrypt=False");
            String query = "DELETE FROM ChessGame WHERE Gid=" + gid + ";";
            SqlCommand cmd = new SqlCommand(query, con);

            con.Open();
            int ret = cmd.ExecuteNonQuery();
            con.Close();
            String json = "";
            return Content(json, "application/json");
        }


        [HttpGet]
        [Route("GetFriends")]
        public IActionResult GetFriends()
        {

            Console.WriteLine("GetFriends");

            String username = Request.Query["username"].ToString();
            SqlConnection con = new SqlConnection("Server=DESKTOP-DKKS7HR; Database=ChessScoutDB;Trusted_Connection=True; Encrypt=False");
            SqlDataAdapter da = new SqlDataAdapter("SELECT * FROM Users WHERE username= '" + username + "' ;", con);
            DataTable dt = new DataTable();
            da.Fill(dt);
            var resp = new List<User>();

            if (dt.Rows.Count > 0)
            {
                for (int i = 0; i < dt.Rows.Count; i++)
                {
                    User user = new User();
                    user.Uid = Convert.ToInt32(dt.Rows[i]["uid"]);
                    user.Email = Convert.ToString(dt.Rows[i]["email"]);
                    user.Username = Convert.ToString(dt.Rows[i]["username"]);
                    user.Pass = Convert.ToString(dt.Rows[i]["pass"]);
                    user.Country = Convert.ToString(dt.Rows[i]["country"]);
                    user.Birthday = Convert.ToDateTime(dt.Rows[i]["birthday"]);

                    resp.Add(user);
                }
                Response.StatusCode = 200;
            }
            else
            {
                Response.StatusCode = 404;

            }
            int uid = (int)resp[0].Uid;
            con = new SqlConnection("Server=DESKTOP-DKKS7HR; Database=ChessScoutDB;Trusted_Connection=True; Encrypt=False");
            da = new SqlDataAdapter("SELECT * FROM FriendRelations WHERE uid1= " + uid + " OR uid2 = " + uid + " ;", con);
            dt = new DataTable();
            da.Fill(dt);

            List<int> uids = new List<int>();
            if (dt.Rows.Count > 0)
            {
                int u1;
                for (int i = 0; i < dt.Rows.Count; i++)
                {

                    u1 = Convert.ToInt32(dt.Rows[i]["uid1"]);
                    if (u1 == uid)
                    {
                        u1 = Convert.ToInt32(dt.Rows[i]["uid2"]);
                        uids.Add(u1);
                    }
                    else
                    {

                        uids.Add(u1);
                    }

                }
                Response.StatusCode = 200;
            }
            else
            {
                Response.StatusCode = 404;

            }

            List<Friend> friends = new List<Friend>();

            if (uids.Count > 0)
            {
                for (int i = 0; i < uids.Count; i++)
                {
                    Friend friend = new Friend();
                    con = new SqlConnection("Server=DESKTOP-DKKS7HR; Database=ChessScoutDB;Trusted_Connection=True; Encrypt=False");
                    da = new SqlDataAdapter("SELECT * FROM Users WHERE uid= " + uids[i] + " ;", con);
                    dt = new DataTable();
                    da.Fill(dt);

                    if (dt.Rows.Count > 0)
                    {

                        friend.uid = Convert.ToInt32(dt.Rows[0]["uid"]);
                        friend.username = Convert.ToString(dt.Rows[0]["username"]);

                        friends.Add(friend);
                        Response.StatusCode = 200;
                    }
                    else
                    {
                        Response.StatusCode = 404;

                    }


                }
                Response.StatusCode = 200;
            }
            else
            {
                Response.StatusCode = 404;

            }


            String json = JsonConvert.SerializeObject(friends);

            return Content(json, "application/json");
        }

        [HttpGet]
        [Route("SearchUsers")]
        public IActionResult SearchUsers()
        {

            Console.WriteLine("SearchUsers");
            String username = Request.Query["username"].ToString();
            String searchFriend = Request.Query["searchFriend"].ToString();

            
            Console.WriteLine(searchFriend);

            SqlConnection con = new SqlConnection("Server=DESKTOP-DKKS7HR; Database=ChessScoutDB;Trusted_Connection=True; Encrypt=False");
            SqlDataAdapter da = new SqlDataAdapter("SELECT * FROM Users WHERE username= '" + username + "' ;", con);
            DataTable dt = new DataTable();
            da.Fill(dt);
            List<User> resp = new List<User>();

            if (dt.Rows.Count > 0)
            {
                for (int i = 0; i < dt.Rows.Count; i++)
                {
                    User user = new User();
                    user.Uid = Convert.ToInt32(dt.Rows[i]["uid"]);
                    user.Email = Convert.ToString(dt.Rows[i]["email"]);
                    user.Username = Convert.ToString(dt.Rows[i]["username"]);
                    user.Pass = Convert.ToString(dt.Rows[i]["pass"]);
                    user.Country = Convert.ToString(dt.Rows[i]["country"]);
                    user.Birthday = Convert.ToDateTime(dt.Rows[i]["birthday"]);

                    resp.Add(user);
                }
                Response.StatusCode = 200;
            }
            else
            {
                Response.StatusCode = 404;

                return Content("", "application/json");

            }
            int uid = (int)resp[0].Uid;

            con = new SqlConnection("Server=DESKTOP-DKKS7HR; Database=ChessScoutDB;Trusted_Connection=True; Encrypt=False");
            da = new SqlDataAdapter("SELECT * FROM Users WHERE username= '" + searchFriend + "' AND uid <> " + uid + ";", con);
            dt = new DataTable();
            da.Fill(dt);
            resp = new List<User>();

            if (dt.Rows.Count > 0)
            {
                for (int i = 0; i < dt.Rows.Count; i++)
                {
                    User user = new User();
                    user.Uid = Convert.ToInt32(dt.Rows[i]["uid"]);
                    user.Email = Convert.ToString(dt.Rows[i]["email"]);
                    user.Username = Convert.ToString(dt.Rows[i]["username"]);
                    user.Pass = Convert.ToString(dt.Rows[i]["pass"]);
                    user.Country = Convert.ToString(dt.Rows[i]["country"]);
                    user.Birthday = Convert.ToDateTime(dt.Rows[i]["birthday"]);

                    resp.Add(user);
                }
                Response.StatusCode = 200;
            }
            else
            {
                Response.StatusCode = 404;
                return Content("", "application/json");

            }

            User user1 = resp[0];
            con = new SqlConnection("Server=DESKTOP-DKKS7HR; Database=ChessScoutDB;Trusted_Connection=True; Encrypt=False");
            da = new SqlDataAdapter("SELECT * FROM FriendRelations WHERE ( uid1 = " + uid + " AND uid2=" + user1.Uid + ") OR (uid2 = " + uid + " AND uid1 = " + user1.Uid + ");", con);
            dt = new DataTable();
            da.Fill(dt);
            String json = "";

            if (dt.Rows.Count > 0)
            {
                Response.StatusCode = 404;
                return Content("", "application/json");
            }
            else
            {

                json = JsonConvert.SerializeObject(user1);
                Response.StatusCode = 200;

            }

            return Content(json, "application/json");
        }

        [HttpGet]
        [Route("DeleteFriend")]
        public IActionResult DeleteFriend()
        {
            String username1 = Request.Query["username1"].ToString();
            String username2 = Request.Query["username2"].ToString();


            SqlConnection con = new SqlConnection("Server=DESKTOP-DKKS7HR; Database=ChessScoutDB;Trusted_Connection=True; Encrypt=False");
            SqlDataAdapter da = new SqlDataAdapter("SELECT * FROM Users WHERE username= '" + username1 + "' ;", con);
            DataTable dt = new DataTable();
            da.Fill(dt);


            User user1 = new User();
            if (dt.Rows.Count > 0)
            {
                for (int i = 0; i < dt.Rows.Count; i++)
                {

                    user1.Uid = Convert.ToInt32(dt.Rows[0]["uid"]);
                    user1.Email = Convert.ToString(dt.Rows[0]["email"]);
                    user1.Username = Convert.ToString(dt.Rows[0]["username"]);
                    user1.Pass = Convert.ToString(dt.Rows[0]["pass"]);
                    user1.Country = Convert.ToString(dt.Rows[0]["country"]);
                    user1.Birthday = Convert.ToDateTime(dt.Rows[0]["birthday"]);



                }
                Response.StatusCode = 200;
            }
            else
            {
                Response.StatusCode = 404;

            }

            con = new SqlConnection("Server=DESKTOP-DKKS7HR; Database=ChessScoutDB;Trusted_Connection=True; Encrypt=False");
            da = new SqlDataAdapter("SELECT * FROM Users WHERE username= '" + username2 + "' ;", con);
            dt = new DataTable();
            da.Fill(dt);

            User user2 = new User();
            if (dt.Rows.Count > 0)
            {
                for (int i = 0; i < dt.Rows.Count; i++)
                {

                    user2.Uid = Convert.ToInt32(dt.Rows[0]["uid"]);
                    user2.Email = Convert.ToString(dt.Rows[0]["email"]);
                    user2.Username = Convert.ToString(dt.Rows[0]["username"]);
                    user2.Pass = Convert.ToString(dt.Rows[0]["pass"]);
                    user2.Country = Convert.ToString(dt.Rows[0]["country"]);
                    user2.Birthday = Convert.ToDateTime(dt.Rows[0]["birthday"]);



                }
                Response.StatusCode = 200;
            }
            else
            {
                Response.StatusCode = 404;

            }

            con = new SqlConnection("Server=DESKTOP-DKKS7HR; Database=ChessScoutDB;Trusted_Connection=True; Encrypt=False");
            String query = "DELETE FROM FriendRelations WHERE (uid1=" + user1.Uid + " OR uid1=" + user2.Uid + ") AND (uid2=" + user1.Uid + " OR uid2=" + user2.Uid + ");";
            SqlCommand cmd = new SqlCommand(query, con);

            con.Open();
            int ret = cmd.ExecuteNonQuery();
            con.Close();



            String json = "";
            return Content(json, "application/json");
        }


        [HttpGet]
        [Route("GetFriendRequests")]
        public IActionResult GetFriendRequests()
        {
            String username = Request.Query["username"].ToString();


            SqlConnection con = new SqlConnection("Server=DESKTOP-DKKS7HR; Database=ChessScoutDB;Trusted_Connection=True; Encrypt=False");
            SqlDataAdapter da = new SqlDataAdapter("SELECT * FROM Users WHERE username= '" + username + "' ;", con);
            DataTable dt = new DataTable();
            da.Fill(dt);


            User user1 = new User();
            if (dt.Rows.Count > 0)
            {

                user1.Uid = Convert.ToInt32(dt.Rows[0]["uid"]);
                user1.Email = Convert.ToString(dt.Rows[0]["email"]);
                user1.Username = Convert.ToString(dt.Rows[0]["username"]);
                user1.Pass = Convert.ToString(dt.Rows[0]["pass"]);
                user1.Country = Convert.ToString(dt.Rows[0]["country"]);
                user1.Birthday = Convert.ToDateTime(dt.Rows[0]["birthday"]);


                Response.StatusCode = 200;
            }
            else
            {
                Response.StatusCode = 404;

            }
            con = new SqlConnection("Server=DESKTOP-DKKS7HR; Database=ChessScoutDB;Trusted_Connection=True; Encrypt=False");
            da = new SqlDataAdapter("SELECT * FROM FriendRequests WHERE Receiver= " + user1.Uid + " ;", con);
            dt = new DataTable();
            da.Fill(dt);
            String json = "";

            List<FriendRequest> friendRequests = new List<FriendRequest>();
            if (dt.Rows.Count > 0)
            {
                for (int i = 0; i < dt.Rows.Count; i++)
                {
                    FriendRequest fq = new FriendRequest();
                    fq.SenderUid = Convert.ToInt32(dt.Rows[0]["Sender"]);
                    fq.ReceiverUid = Convert.ToInt32(dt.Rows[0]["Receiver"]);
                    fq.Receiver = username;

                    friendRequests.Add(fq);
                }
                Response.StatusCode = 200;
            }
            else
            {
                Response.StatusCode = 404;

            }

            if (friendRequests.Count > 0)
            {

                for (int i = 0; i < friendRequests.Count; i++)
                {
                    con = new SqlConnection("Server=DESKTOP-DKKS7HR; Database=ChessScoutDB;Trusted_Connection=True; Encrypt=False");
                    da = new SqlDataAdapter("SELECT * FROM Users WHERE uid= " + friendRequests[i].SenderUid + " ;", con);
                    dt = new DataTable();
                    da.Fill(dt);
                    for (int j = 0; j < dt.Rows.Count; j++)
                    {

                        friendRequests[i].Sender = Convert.ToString(dt.Rows[0]["username"]);
                    }

                }
            }

            json = JsonConvert.SerializeObject(friendRequests);

            return Content(json, "application/json");
        }


        [HttpGet]
        [Route("DeleteRequest")]
        public IActionResult DeleteRequest()
        {
            String SenderUid = Request.Query["SenderUid"].ToString();
            String ReceiverUid = Request.Query["ReceiverUid"].ToString();

            SqlConnection con = new SqlConnection("Server=DESKTOP-DKKS7HR; Database=ChessScoutDB;Trusted_Connection=True; Encrypt=False");
            String query = "DELETE FROM FriendRequests WHERE Sender=" + SenderUid + " AND Receiver=" + ReceiverUid + ";";
            SqlCommand cmd = new SqlCommand(query, con);

            con.Open();
            int ret = cmd.ExecuteNonQuery();
            con.Close();
            String json = "";
            return Content(json, "application/json");
        }

        [HttpGet]
        [Route("AcceptRequest")]
        public IActionResult AcceptRequest()
        {
            String SenderUid = Request.Query["SenderUid"].ToString();
            String ReceiverUid = Request.Query["ReceiverUid"].ToString();

            SqlConnection con = new SqlConnection("Server=DESKTOP-DKKS7HR; Database=ChessScoutDB;Trusted_Connection=True; Encrypt=False");
            String query = "DELETE FROM FriendRequests WHERE Sender=" + SenderUid + " AND Receiver=" + ReceiverUid + ";";
            SqlCommand cmd = new SqlCommand(query, con);

            con.Open();
            int ret = cmd.ExecuteNonQuery();
            con.Close();

            con = new SqlConnection("Server=DESKTOP-DKKS7HR; Database=ChessScoutDB;Trusted_Connection=True; Encrypt=False");
            query = "INSERT INTO FriendRelations VALUES (@sender,@receiver)";
            cmd = new SqlCommand(query, con);

            cmd.Parameters.Add(new SqlParameter("@sender", SenderUid));
            cmd.Parameters.Add(new SqlParameter("@receiver", ReceiverUid));


            con.Open();
            ret = cmd.ExecuteNonQuery();
            con.Close();


            String json = "";
            return Content(json, "application/json");
        }

        [HttpGet]
        [Route("GetMessages")]
        public IActionResult GetMessages() {
            String Sender = Request.Query["Sender"].ToString();
            String Receiver = Request.Query["Receiver"].ToString();

            Console.WriteLine(Sender+" = Sender");
            Console.WriteLine(Receiver + " = Receiver");

            SqlConnection con = new SqlConnection("Server=DESKTOP-DKKS7HR; Database=ChessScoutDB;Trusted_Connection=True; Encrypt=False");
            SqlDataAdapter da = new SqlDataAdapter("SELECT * FROM Users WHERE username= '" + Sender + "' ;", con);
            DataTable dt = new DataTable();
            da.Fill(dt);


            User user1 = new User();
            if (dt.Rows.Count > 0)
            {
                for (int i = 0; i < dt.Rows.Count; i++)
                {

                    user1.Uid = Convert.ToInt32(dt.Rows[0]["uid"]);
                    user1.Email = Convert.ToString(dt.Rows[0]["email"]);
                    user1.Username = Convert.ToString(dt.Rows[0]["username"]);
                    user1.Pass = Convert.ToString(dt.Rows[0]["pass"]);
                    user1.Country = Convert.ToString(dt.Rows[0]["country"]);
                    user1.Birthday = Convert.ToDateTime(dt.Rows[0]["birthday"]);



                }
                Response.StatusCode = 200;
            }
            else
            {
                Response.StatusCode = 404;

            }

            con = new SqlConnection("Server=DESKTOP-DKKS7HR; Database=ChessScoutDB;Trusted_Connection=True; Encrypt=False");
            da = new SqlDataAdapter("SELECT * FROM Users WHERE username= '" + Receiver + "' ;", con);
            dt = new DataTable();
            da.Fill(dt);

            User user2 = new User();
            if (dt.Rows.Count > 0)
            {
                for (int i = 0; i < dt.Rows.Count; i++)
                {

                    user2.Uid = Convert.ToInt32(dt.Rows[0]["uid"]);
                    user2.Email = Convert.ToString(dt.Rows[0]["email"]);
                    user2.Username = Convert.ToString(dt.Rows[0]["username"]);
                    user2.Pass = Convert.ToString(dt.Rows[0]["pass"]);
                    user2.Country = Convert.ToString(dt.Rows[0]["country"]);
                    user2.Birthday = Convert.ToDateTime(dt.Rows[0]["birthday"]);



                }
                Response.StatusCode = 200;
            }
            else
            {
                Response.StatusCode = 404;

            }

            con = new SqlConnection("Server=DESKTOP-DKKS7HR; Database=ChessScoutDB;Trusted_Connection=True; Encrypt=False");
            da = new SqlDataAdapter("SELECT * FROM Message WHERE (uidSender=" + user1.Uid + " OR uidReceiver=" + user1.Uid + ") AND (uidSender=" + user2.Uid + " OR uidReceiver=" + user2.Uid + ") ORDER BY Date ;", con);
            dt = new DataTable();
            da.Fill(dt);

            List<ChessScout.Models.Message> messages = new List<ChessScout.Models.Message>();
            if (dt.Rows.Count > 0)
            {
                for (int i = 0; i < dt.Rows.Count; i++)
                {
                    ChessScout.Models.Message message = new ChessScout.Models.Message();

                    message.UidSender = Convert.ToInt32(dt.Rows[i]["uidSender"]);
                    message.UidReceiver = Convert.ToInt32(dt.Rows[i]["uidReceiver"]);
                    message.MessageText = Convert.ToString(dt.Rows[i]["MessageText"]);
                    message.Seen = Convert.ToInt32(dt.Rows[i]["seen"]);
                    message.Date = Convert.ToDateTime(dt.Rows[i]["Date"]);

                    messages.Add(message);

                }
                Response.StatusCode = 200;
            }
            else
            {
                Response.StatusCode = 404;

            }


            String json = JsonConvert.SerializeObject(messages);
            return Content(json, "application/json");
        }


        [HttpGet]
        [Route("SendMessage")]
        public IActionResult SendMessage()
        {
            String Sender = Request.Query["Sender"].ToString();
            String Receiver = Request.Query["Receiver"].ToString();
            String MessageText = Request.Query["MessageText"].ToString();

            Console.WriteLine(Sender + " = Sender");
            Console.WriteLine(Receiver + " = Receiver");

            SqlConnection con = new SqlConnection("Server=DESKTOP-DKKS7HR; Database=ChessScoutDB;Trusted_Connection=True; Encrypt=False");
            SqlDataAdapter da = new SqlDataAdapter("SELECT * FROM Users WHERE username= '" + Sender + "' ;", con);
            DataTable dt = new DataTable();
            da.Fill(dt);


            User user1 = new User();
            if (dt.Rows.Count > 0)
            {
                for (int i = 0; i < dt.Rows.Count; i++)
                {

                    user1.Uid = Convert.ToInt32(dt.Rows[0]["uid"]);
                    user1.Email = Convert.ToString(dt.Rows[0]["email"]);
                    user1.Username = Convert.ToString(dt.Rows[0]["username"]);
                    user1.Pass = Convert.ToString(dt.Rows[0]["pass"]);
                    user1.Country = Convert.ToString(dt.Rows[0]["country"]);
                    user1.Birthday = Convert.ToDateTime(dt.Rows[0]["birthday"]);



                }
                Response.StatusCode = 200;
            }
            else
            {
                Response.StatusCode = 404;

            }

            con = new SqlConnection("Server=DESKTOP-DKKS7HR; Database=ChessScoutDB;Trusted_Connection=True; Encrypt=False");
            da = new SqlDataAdapter("SELECT * FROM Users WHERE username= '" + Receiver + "' ;", con);
            dt = new DataTable();
            da.Fill(dt);

            User user2 = new User();
            if (dt.Rows.Count > 0)
            {
                for (int i = 0; i < dt.Rows.Count; i++)
                {

                    user2.Uid = Convert.ToInt32(dt.Rows[0]["uid"]);
                    user2.Email = Convert.ToString(dt.Rows[0]["email"]);
                    user2.Username = Convert.ToString(dt.Rows[0]["username"]);
                    user2.Pass = Convert.ToString(dt.Rows[0]["pass"]);
                    user2.Country = Convert.ToString(dt.Rows[0]["country"]);
                    user2.Birthday = Convert.ToDateTime(dt.Rows[0]["birthday"]);



                }
                Response.StatusCode = 200;
            }
            else
            {
                Response.StatusCode = 404;

            }

            con = new SqlConnection("Server=DESKTOP-DKKS7HR; Database=ChessScoutDB;Trusted_Connection=True; Encrypt=False");
            String query = "INSERT INTO Message VALUES (@sender,@receiver,@message,@seen,@date)";
            SqlCommand cmd = new SqlCommand(query, con);
            int seen = 0;
            cmd.Parameters.Add(new SqlParameter("@sender", user1.Uid));
            cmd.Parameters.Add(new SqlParameter("@receiver", user2.Uid));
            cmd.Parameters.Add(new SqlParameter("@message", MessageText));
            cmd.Parameters.Add(new SqlParameter("@seen", seen));
            cmd.Parameters.Add(new SqlParameter("@date", DateTime.Now));

            con.Open();
            int ret = cmd.ExecuteNonQuery();
            con.Close();

            
            String json = "";
            return Content(json, "application/json");
        }

        [HttpGet]
        [Route("CreateRequest")]
        public IActionResult CreateRequest()
        {
            String Sender = Request.Query["Sender"].ToString();
            String Receiver = Request.Query["Receiver"].ToString();

            SqlConnection con = new SqlConnection("Server=DESKTOP-DKKS7HR; Database=ChessScoutDB;Trusted_Connection=True; Encrypt=False");
            SqlDataAdapter da = new SqlDataAdapter("SELECT * FROM Users WHERE username= '" + Sender + "' ;", con);
            DataTable dt = new DataTable();
            da.Fill(dt);


            User user1 = new User();
            if (dt.Rows.Count > 0)
            {
                for (int i = 0; i < dt.Rows.Count; i++)
                {

                    user1.Uid = Convert.ToInt32(dt.Rows[0]["uid"]);
                    user1.Email = Convert.ToString(dt.Rows[0]["email"]);
                    user1.Username = Convert.ToString(dt.Rows[0]["username"]);
                    user1.Pass = Convert.ToString(dt.Rows[0]["pass"]);
                    user1.Country = Convert.ToString(dt.Rows[0]["country"]);
                    user1.Birthday = Convert.ToDateTime(dt.Rows[0]["birthday"]);



                }
                Response.StatusCode = 200;
            }
            else
            {
                Response.StatusCode = 404;

            }

            con = new SqlConnection("Server=DESKTOP-DKKS7HR; Database=ChessScoutDB;Trusted_Connection=True; Encrypt=False");
            da = new SqlDataAdapter("SELECT * FROM Users WHERE username= '" + Receiver + "' ;", con);
            dt = new DataTable();
            da.Fill(dt);

            User user2 = new User();
            if (dt.Rows.Count > 0)
            {
                for (int i = 0; i < dt.Rows.Count; i++)
                {

                    user2.Uid = Convert.ToInt32(dt.Rows[0]["uid"]);
                    user2.Email = Convert.ToString(dt.Rows[0]["email"]);
                    user2.Username = Convert.ToString(dt.Rows[0]["username"]);
                    user2.Pass = Convert.ToString(dt.Rows[0]["pass"]);
                    user2.Country = Convert.ToString(dt.Rows[0]["country"]);
                    user2.Birthday = Convert.ToDateTime(dt.Rows[0]["birthday"]);



                }
                Response.StatusCode = 200;
            }
            else
            {
                Response.StatusCode = 404;

            }

            con = new SqlConnection("Server=DESKTOP-DKKS7HR; Database=ChessScoutDB;Trusted_Connection=True; Encrypt=False");
            String query = "INSERT INTO FriendRequests VALUES (@sender,@receiver)";
            SqlCommand cmd = new SqlCommand(query, con);

            cmd.Parameters.Add(new SqlParameter("@sender", user1.Uid));
            cmd.Parameters.Add(new SqlParameter("@receiver", user2.Uid));

            con.Open();
            int ret = cmd.ExecuteNonQuery();
            con.Close();

            String json = "";
            return Content(json, "application/json");
        }
    }


}
