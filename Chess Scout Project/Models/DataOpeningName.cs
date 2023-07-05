namespace ChessScout.Models
{
    public class DataOpeningName
    {
        public DataOpeningName(string ECO,string Name,double PRate,double WRate) { 
            this.ECO = ECO;
            this.Name = Name;
            this.PRate = PRate;
            this.WRate = WRate;
        }

        public string ECO;
        public string Name;
        public double PRate;
        public double WRate;

    }
}
