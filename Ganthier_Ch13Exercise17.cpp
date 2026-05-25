#include <iostream>
#include <random>
#include <stdexcept>
#include <iomanip>
#include <sstream>

using namespace std;

int main() {
    // ========================================================================
    // Requirement 1: C++11 Random Number Generator Setup
    // ========================================================================
    // std::random_device obtains a random seed from the hardware
    random_device rd; 
    
    // std::mt19937 is a standard Mersenne Twister engine
    mt19937 gen(rd()); 
    
    // std::uniform_real_distribution generates real numbers (doubles)
    // We set the inclusive range between 10.0 and 100.0
    uniform_real_distribution<double> dist(10.0, 100.0);

    // Output formatting for console
    cout << "====================================================\n";
    cout << "          Reactor Temperature Simulation            \n";
    cout << "====================================================\n";
    cout << "Safe operating range : 10.0C - 100.0C\n";
    cout << "CRITICAL DANGER ZONE : 85.0C -  90.0C (Triggers Exception)\n";
    cout << "Taking 25 system readings...\n\n";

    // Setup output to display 2 decimal places consistently
    cout << fixed << setprecision(2);

    // Loop exactly 25 times to generate 25 random real numbers
    for (int i = 1; i <= 25; ++i) {
        
        // ====================================================================
        // Requirement 2: Exception Management (try/catch block)
        // ====================================================================
        try {
            // Generate the random real number
            double reading = dist(gen);

            // Check if the reading falls into the critical danger zone
            if (reading >= 85.0 && reading <= 90.0) {
                
                // Format the error message dynamically
                ostringstream errorMsg;
                errorMsg << fixed << setprecision(2) << reading;
                
                // Throw a standard runtime_error exception
                throw runtime_error("CRITICAL OVERHEAT ALERT! Temp at " + errorMsg.str() + "C");
            }

            // If no exception is thrown, normal execution continues here
            cout << "[Reading " << setw(2) << i << "] : " 
                 << setw(6) << reading << "C - Normal\n";

        } 
        catch (const runtime_error& e) {
            // The catch block intercepts the thrown exception
            // Instead of the program crashing, we handle the error gracefully
            cout << "[Reading " << setw(2) << i << "] : " 
                 << "*** EXCEPTION CAUGHT *** " << e.what() << "\n";
                 
            // In a real application, you might engage cooling systems here
        }
    }

    cout << "\n====================================================\n";
    cout << "Simulation complete. Reactor shutdown successful.\n";

    return 0;
}

