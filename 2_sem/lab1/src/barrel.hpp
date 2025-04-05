class Barrel{
    private:
        double m_volume, m_alch;
    
    public:
        Barrel(double volume=0, double alch=0);
        double concentration();
        void pour_in(Barrel& barrel);
};