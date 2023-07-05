
using Newtonsoft.Json;
using System;
using System.Collections.Generic;

namespace ChessScout.Models;

public partial class ScoutData
{
    [JsonProperty("PlayerName")]
    public string? PlayerName { get; set; }

    [JsonProperty("UserName")]
    public string? UserName { get; set; }

    [JsonProperty("Elo")]
    public int? Elo { get; set; }

    [JsonProperty("preferted_openings_data")]
    public string? preferted_openings_data { get; set; }

    [JsonProperty("games")]
    public string? games { get; set; }

    [JsonProperty("opening_tree_data")]
    public string? opening_tree_data { get; set; }

    public int? Pid { get; set; }

    public int? Uid { get; set; }   
}
