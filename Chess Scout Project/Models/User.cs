using System;
using System.Collections.Generic;

namespace ChessScout.Models;

public partial class User
{
    public int? Uid { get; set; }

    public string? Username { get; set; }

    public string? Pass { get; set; }

    public string? Email { get; set; }

    public string? Country { get; set; }

    public DateTime? Birthday { get; set; }
}
