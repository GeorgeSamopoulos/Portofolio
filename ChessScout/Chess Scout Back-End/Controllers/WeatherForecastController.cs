using Microsoft.AspNetCore.Mvc;
using System.Data;
using ChessScout.Models;
using Microsoft.Data.SqlClient;
using Newtonsoft.Json;

namespace ChessScout.Controllers
{
    [ApiController]
    [Route("api/[controller]")]
    public class WeatherForecastController : ControllerBase
    {
        private readonly ChessScoutDbContext _dbcontext;
        public WeatherForecastController(ChessScoutDbContext _context) { 
            

            _dbcontext = _context;
        }




    }
}