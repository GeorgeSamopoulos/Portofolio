namespace ChessScout.Models
{
    public class MoveTree
    {
        public MoveTree(double WRate,double PRate,string Move) {
            this.WRate = WRate;
            this.PRate = PRate;
            this.Move = Move; 
        
        } 

        public double WRate { get; set; }

        public double PRate { get; set; }

        public string Move { get; set; }
    }

    public class MoveTreeResponse{ 
    
       public int NumOfDownloaded { get; set;}
       public int depth { get; set;}
       public List <MoveTree> datamoves { get; set;}
    
    }
}
