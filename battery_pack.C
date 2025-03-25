#include<iostream>
#include<stdint.h>
#include<list>
#include<unordered_map>
#include<map>

#define MAX_SOC 100
#define MIN_SOC 0

using namespace std;

class Cell{
    public:
    int id;
    float voltage;
    float current;
    float temperature;

    Cell(int cell_id,float volts, float curr){
        id=cell_id;
        voltage=volts;
        current=curr;
    }
};
 
class Battery_Pack{
    public:
    float voltage;
    float current;
    float Ah_value;
    list <Cell> cell_count;

    Battery_Pack(int cells){
        for(int i=1;i<=cells;i++){
            cell_count.push_back(Cell(i, 3.7,3.0));
         //   cout << "Cell ID:" << 
        }
    }

};




void get_current(){

}

class Battery_SOC_Model{
    private:
    float CellVoltage;
    float Current_capacity;
    float SOC;
    float SOC_lookup[MAX_SOC+1];
    float Voltage_lookup[MAX_SOC+1];
    float arr[101][2];


    float Interpolation(float x0, float x1, float y0, float y1, float x ){
        return y0 + ((y1 - y0) / (x1 - x0)) * (x - x0);
    }
    
    //Create an array for SOC and voltage(2D array), write a search algorithm to find the SOC and voltage

    public:
    Battery_SOC_Model(){
        float voltage_init = 3.0;
        // SOC = soc;
        // CellVoltage = Interpolation(0,100,3.0,4.2, SOC);
        SOC=100;
        for(int i=0;i<=MAX_SOC;i++){
            SOC_lookup[i] = i;
            Voltage_lookup[i] =  voltage_init;
            voltage_init +=0.012;
            arr[i][0]=SOC_lookup[i];
            arr[i][1]=Voltage_lookup[i];
        }
    }

    float get_voltage(float soc_val){
        int i=0;
        while(arr[i][0] != (int)soc_val){
            i++;
        }
        if(arr[i][0] == (int)soc_val){
            CellVoltage= Interpolation(arr[i][0], arr[i+1][0], arr[i][1], arr[i+1][1],soc_val);
        }
        cout << "Mapped voltage is: " <<CellVoltage <<endl;
        return CellVoltage;
        
    }



    void run(){
        cout << "SOC:" << SOC << "Voltage: " << CellVoltage <<endl;

    }


    class Accumulator{ //can put inside Battery_Pack class
        public:
        float current;
        float charge_Ah;
        float discharge_Ah;
    
    
        Accumulator(){
            current = 0;
            charge_Ah = 0;
            discharge_Ah = 0;
        }
    
        float get_status(float input_current){  //run in a loop and plot as graph later
            Battery_SOC_Model batt;
            printf("Enter initial SOC:");
            scanf("%f",&batt.SOC);

            printf("Enter current capacity of battery:");
            scanf("%f",&batt.Current_capacity);
            if(input_current>0){
                charge_Ah += input_current*10;
                batt.SOC = batt.SOC + ((charge_Ah/batt.Current_capacity)*100);
                if(batt.SOC >=100){
                    printf("Battery fully charged\n");
                    batt.SOC = 100;
                    return batt.SOC;
                }
                cout << "Battery pack is Charging"<<endl;
                

            }
            else if(input_current==0){
                cout <<"Idle" <<endl;
            }
            else{
                discharge_Ah += input_current*10;
                cout << "Battery Pack Discharging"<<endl;
                batt.SOC = batt.SOC + ((discharge_Ah/batt.Current_capacity)*100);
                if(batt.SOC <=0){
                    printf("Battery completely discharged\n");
                    batt.SOC = 0;
                    return batt.SOC;
                }
                
            }
            cout << "Battery SOC is: "<<batt.SOC <<endl;
            return batt.SOC;
        }
    
        float capacity_calc(float curr){
    
        }
        //takes in current and present SOC and provides new SOC as output
        //Or take current and give charging and discharging capacity
        //charge_Ah_accumulated discharge_Ah_accumulated
        //net_Ah accumulated = (charge_Ah - discharge_Ah) -need not be in accumulator class
        // function in accumulator to calculate net_Ah calculated
        //set netAh and get net_Ah
    //every time this function
    };


    //build a relation wherein a lookup table for every value of SOC from 0 to 100, there should be an associated voltage.
    //every time you pass a current value, use the amphour accumulator class, estimate the SOC, perform a lookup and determine voltage using linear interpolation
    //Ah capacity of the cell(assume==10). Determine cell voltage and pack voltage for a certain time frame
    //Initialize cell voltage based on SOC
    //Battery Model.run
    //Define a destructor

};

void delay(int milliseconds) {
    volatile int x;  // to prevent optimization
    for (int i = 0; i < milliseconds * 1000; ++i) {
        x = i;  // no-op to burn CPU cycles
    }
}

//To calculate SOC, current SOC = Previous SOC + netAh accumulated/capacity


int main(){
    Battery_Pack batteries(12);
    // for(Cell teotal :batteries.cell_count){
    //     cout << "Cell ID: " << teotal.id << "Voltage: "<< teotal.voltage  \
    //     <<"Current Capacity: "<<teotal.current <<endl;
    // }
    Battery_SOC_Model battery;
    battery.get_voltage(75);
    Battery_SOC_Model::Accumulator current_draw;
    float soc_current = current_draw.get_status(-5.789);
    battery.get_voltage(soc_current);
}