using System;
using System.Collections.Generic;

namespace ChessScout.Models;

public partial class ScoutProfile
{
    public int? Pid { get; set; }

    public int? Uid { get; set; }

    public int? Number { get; set; }

    public string? PlayersName { get; set; }

    public DateTime? SaveDate { get; set; }
}
