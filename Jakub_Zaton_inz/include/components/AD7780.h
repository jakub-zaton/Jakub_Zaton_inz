#ifndef AD7780_HH
#define AD7780_HH

class AD7780{
   
    private:
        int AD7780_SCK;
        int AD7780_MISO;
        int AD7780_PWDOWN;

        long calZero = 0;
        long calLoad = 0;
        long calCoeff = 0;
        float outputWeight = 0;

    public:
        void begin(int AD7780_SCK_, int AD7780_MISO_, int AD7780_PWDOWN_);
        int readDataRaw();
        float calibration(int knownMass);
        float readData();
        void set_calCOeff(long calCoeff_);
        void set_offset(long calZero_);
        void tare();
        long get_offset();
        long get_calFactor();
};

#endif