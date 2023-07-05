using System;
using System.Collections.Generic;

namespace ChessScout.Models;

public partial class FriendRequest
{
    public int? Uid1 { get; set; }

    public int? Uid2 { get; set; }
    public int? SenderUid { get; set; }

    public int? ReceiverUid { get; set; }
    
    public string? Sender { get; set; }

    public string? Receiver { get; set; }


}
