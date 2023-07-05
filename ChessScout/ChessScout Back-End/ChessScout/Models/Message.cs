using System;
using System.Collections.Generic;

namespace ChessScout.Models;

public partial class Message
{
    public int? UidSender { get; set; }

    public int? UidReceiver { get; set; }

    public string? MessageText { get; set; }

    public int? Seen { get; set; }

    public DateTime? Date { get; set; }
}
