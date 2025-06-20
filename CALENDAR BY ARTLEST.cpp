/*
================================================================================
PROFESSIONAL C++ CALENDAR IMPLEMENTATION SYSTEM
================================================================================
Purpose: Comprehensive calendar generation with date calculations and
         statistical analysis for temporal data processing
Author: Professional C++ Development Team
Code hints and optimizations by artlest
Platform: Cross-platform compatible (Online IDEs, Standard Compilers)
Standards: C++11 Standard Library Implementation
================================================================================
*/

#include <iostream>      // Provides standard input/output stream functionality
#include <iomanip>       // Enables formatted output manipulation and precision control
#include <string>        // Implements string class for text processing operations
#include <vector>        // Provides dynamic array container for data storage
#include <algorithm>     // Contains algorithmic functions for data manipulation

using namespace std;

/*
================================================================================
FUNCTION DECLARATIONS AND PROTOTYPES
================================================================================
*/

// Function determines if specified year is a leap year using algorithmic calculation
bool calculate_leap_year_status(int target_year);

// Function calculates total days in specified month considering leap year conditions
int calculate_month_day_count(int target_month, int target_year);

// Function determines the starting day of week for specified month and year
int calculate_month_starting_day(int target_month, int target_year);

// Function generates and displays formatted calendar for specified month
void generate_monthly_calendar_display(int target_month, int target_year);

// Function performs statistical analysis on calendar data patterns
void execute_calendar_statistics_analysis(int target_year);

// Function validates date input parameters within acceptable ranges
bool validate_date_input_parameters(int month_value, int year_value);

// Function displays formatted program header with identification information
void display_program_identification_header();

// Function converts numeric month value to corresponding text representation
string convert_month_number_to_text(int month_number);

// Function calculates day of year for specified date parameters
int calculate_day_of_year_position(int day_value, int month_value, int year_value);

// Function displays progress indicator for calendar generation operations
void display_calendar_generation_progress(int current_month, int total_months);

/*
================================================================================
MAIN PROGRAM EXECUTION ENTRY POINT
================================================================================
*/

int main() {
    // Initialize primary execution parameters for calendar demonstration
    const int demonstration_year = 2025;
    const int total_demonstration_months = 12;
    int current_processing_month = 1;
    
    // Display professional program identification header
    display_program_identification_header();
    
    // Validate demonstration year parameters before processing
    if (validate_date_input_parameters(1, demonstration_year)) {
        cout << "Calendar Generation Parameters Validated Successfully" << endl;
        cout << "Target Year: " << demonstration_year << endl;
        cout << "Processing Mode: Complete Annual Calendar" << endl;
        cout << string(60, '=') << endl;
        
        // Execute comprehensive calendar generation for entire year
        while (current_processing_month <= total_demonstration_months) {
            cout << "\n" << string(50, '-') << endl;
            cout << "PROCESSING MONTH: " << current_processing_month 
                 << " (" << convert_month_number_to_text(current_processing_month) << ")" << endl;
            cout << string(50, '-') << endl;
            
            // Generate formatted calendar display for current month
            generate_monthly_calendar_display(current_processing_month, demonstration_year);
            
            // Display processing progress indicator
            display_calendar_generation_progress(current_processing_month, total_demonstration_months);
            
            // Increment month processing counter
            current_processing_month++;
        }
        
        // Execute statistical analysis on generated calendar data
        cout << "\n" << string(60, '=') << endl;
        cout << "EXECUTING CALENDAR STATISTICAL ANALYSIS" << endl;
        cout << string(60, '=') << endl;
        execute_calendar_statistics_analysis(demonstration_year);
        
    } else {
        cout << "ERROR: Invalid calendar parameters detected." << endl;
        return 1; // Indicates parameter validation failure
    }
    
    // Display program completion status and summary
    cout << "\n" << string(60, '=') << endl;
    cout << "CALENDAR GENERATION COMPLETED SUCCESSFULLY" << endl;
    cout << "Year Processed: " << demonstration_year << endl;
    cout << "Months Generated: " << total_demonstration_months << endl;
    cout << "Leap Year Status: " << (calculate_leap_year_status(demonstration_year) ? "TRUE" : "FALSE") << endl;
    cout << string(60, '=') << endl;
    
    return 0; // Indicates successful program termination
}

/*
================================================================================
LEAP YEAR CALCULATION ALGORITHM IMPLEMENTATION
================================================================================
*/

bool calculate_leap_year_status(int target_year) {
    // Implements standard Gregorian calendar leap year determination algorithm
    // Year is leap if divisible by 4, except century years must be divisible by 400
    if (target_year % 400 == 0) {
        return true; // Century year divisible by 400 is leap year
    } else if (target_year % 100 == 0) {
        return false; // Century year not divisible by 400 is not leap year
    } else if (target_year % 4 == 0) {
        return true; // Non-century year divisible by 4 is leap year
    } else {
        return false; // Year not divisible by 4 is not leap year
    }
}

/*
================================================================================
MONTH DAY COUNT CALCULATION FUNCTION
================================================================================
*/

int calculate_month_day_count(int target_month, int target_year) {
    // Array stores standard day counts for each month (non-leap year)
    int standard_month_days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    // Validate month parameter within acceptable range
    if (target_month < 1 || target_month > 12) {
        return 0; // Return zero for invalid month parameter
    }
    
    // Adjust February day count for leap year conditions
    if (target_month == 2 && calculate_leap_year_status(target_year)) {
        return 29; // February has 29 days in leap years
    } else {
        return standard_month_days[target_month - 1]; // Return standard day count
    }
}

/*
================================================================================
MONTH STARTING DAY CALCULATION ALGORITHM
================================================================================
*/

int calculate_month_starting_day(int target_month, int target_year) {
    // Implements Zeller's Congruence algorithm for day-of-week calculation
    // Adjusts month and year values for algorithm requirements
    int adjusted_month = target_month;
    int adjusted_year = target_year;
    
    // Zeller's algorithm treats January and February as months 13 and 14 of previous year
    if (adjusted_month < 3) {
        adjusted_month += 12;
        adjusted_year--;
    }
    
    // Calculate century and year components for Zeller's formula
    int century_component = adjusted_year / 100;
    int year_component = adjusted_year % 100;
    
    // Apply Zeller's Congruence formula for day-of-week determination
    int day_of_week = (1 + (13 * (adjusted_month + 1)) / 5 + year_component + 
                       year_component / 4 + century_component / 4 - 2 * century_component) % 7;
    
    // Convert Zeller's result (0=Saturday) to standard format (0=Sunday)
    return (day_of_week + 6) % 7;
}

/*
================================================================================
MONTHLY CALENDAR DISPLAY GENERATION FUNCTION
================================================================================
*/

void generate_monthly_calendar_display(int target_month, int target_year) {
    // Retrieve month-specific parameters for calendar generation
    int month_day_count = calculate_month_day_count(target_month, target_year);
    int starting_day_position = calculate_month_starting_day(target_month, target_year);
    string month_text_representation = convert_month_number_to_text(target_month);
    
    // Display formatted calendar header with month and year information
    cout << "\n" << setw(20) << month_text_representation << " " << target_year << endl;
    cout << string(28, '-') << endl;
    
    // Display day-of-week column headers
    cout << " Su Mo Tu We Th Fr Sa" << endl;
    
    // Generate leading spaces for first week alignment
    int calendar_position_counter = 0;
    for (int leading_space_counter = 0; leading_space_counter < starting_day_position; leading_space_counter++) {
        cout << "   "; // Three spaces per calendar position
        calendar_position_counter++;
    }
    
    // Generate calendar days with proper formatting and positioning
    for (int current_day = 1; current_day <= month_day_count; current_day++) {
        cout << setw(3) << current_day; // Right-aligned day number
        calendar_position_counter++;
        
        // Insert line break after Saturday (position 7) for new week
        if (calendar_position_counter % 7 == 0) {
            cout << endl;
        }
    }
    
    // Add final newline if month doesn't end on Saturday
    if (calendar_position_counter % 7 != 0) {
        cout << endl;
    }
    
    // Display month statistics and analysis
    cout << "\nMonth Analysis:" << endl;
    cout << "  Total Days: " << month_day_count << endl;
    cout << "  Starting Day: " << starting_day_position << " (0=Sunday)" << endl;
    cout << "  Weekends: " << ((month_day_count + starting_day_position + 6) / 7) << endl;
}

/*
================================================================================
CALENDAR STATISTICAL ANALYSIS FUNCTION
================================================================================
*/

void execute_calendar_statistics_analysis(int target_year) {
    // Initialize statistical accumulation variables
    int total_year_days = 0;
    int total_weekend_days = 0;
    int total_weekday_count = 0;
    vector<int> month_length_distribution;
    
    // Process each month for statistical data collection
    for (int analysis_month = 1; analysis_month <= 12; analysis_month++) {
        int current_month_days = calculate_month_day_count(analysis_month, target_year);
        int month_starting_day = calculate_month_starting_day(analysis_month, target_year);
        
        // Accumulate total day count for year
        total_year_days += current_month_days;
        
        // Store month length for distribution analysis
        month_length_distribution.push_back(current_month_days);
        
        // Calculate weekend days for current month
        int month_weekend_days = 0;
        for (int day_counter = 1; day_counter <= current_month_days; day_counter++) {
            int day_of_week = (month_starting_day + day_counter - 1) % 7;
            if (day_of_week == 0 || day_of_week == 6) { // Sunday or Saturday
                month_weekend_days++;
            }
        }
        total_weekend_days += month_weekend_days;
    }
    
    // Calculate derived statistical metrics
    total_weekday_count = total_year_days - total_weekend_days;
    double weekend_percentage = (double(total_weekend_days) / total_year_days) * 100.0;
    
    // Display comprehensive statistical analysis results
    cout << "ANNUAL CALENDAR STATISTICS REPORT" << endl;
    cout << string(40, '-') << endl;
    cout << "Target Year: " << target_year << endl;
    cout << "Leap Year Status: " << (calculate_leap_year_status(target_year) ? "TRUE" : "FALSE") << endl;
    cout << "Total Days: " << total_year_days << endl;
    cout << "Weekend Days: " << total_weekend_days << endl;
    cout << "Weekday Count: " << total_weekday_count << endl;
    cout << "Weekend Percentage: " << fixed << setprecision(1) << weekend_percentage << "%" << endl;
    
    // Calculate and display month length distribution statistics
    sort(month_length_distribution.begin(), month_length_distribution.end());
    cout << "\nMonth Length Distribution:" << endl;
    cout << "  Shortest Month: " << month_length_distribution[0] << " days" << endl;
    cout << "  Longest Month: " << month_length_distribution[11] << " days" << endl;
    cout << "  Average Month Length: " << fixed << setprecision(1) 
         << (double(total_year_days) / 12.0) << " days" << endl;
}

/*
================================================================================
INPUT VALIDATION FUNCTION IMPLEMENTATION
================================================================================
*/

bool validate_date_input_parameters(int month_value, int year_value) {
    // Validate month parameter within acceptable range (1-12)
    if (month_value < 1 || month_value > 12) {
        return false; // Month value outside valid range
    }
    
    // Validate year parameter within reasonable range (1900-2100)
    if (year_value < 1900 || year_value > 2100) {
        return false; // Year value outside reasonable range
    }
    
    return true; // All parameters within valid ranges
}

/*
================================================================================
PROGRAM HEADER DISPLAY FUNCTION
================================================================================
*/

void display_program_identification_header() {
    cout << string(60, '=') << endl;
    cout << "PROFESSIONAL C++ CALENDAR GENERATION SYSTEM" << endl;
    cout << "Advanced Date Processing and Statistical Analysis" << endl;
    cout << string(60, '=') << endl;
    cout << "Features: Leap Year Calculation, Monthly Display, Statistics" << endl;
    cout << "Algorithm: Zeller's Congruence for Day-of-Week Determination" << endl;
    cout << string(60, '=') << endl;
}

/*
================================================================================
MONTH NUMBER TO TEXT CONVERSION FUNCTION
================================================================================
*/

string convert_month_number_to_text(int month_number) {
    // Array contains full month names for text conversion
    string month_names[] = {"January", "February", "March", "April", "May", "June",
                           "July", "August", "September", "October", "November", "December"};
    
    // Validate month number and return corresponding text
    if (month_number >= 1 && month_number <= 12) {
        return month_names[month_number - 1];
    } else {
        return "Invalid Month"; // Return error indicator for invalid input
    }
}

/*
================================================================================
DAY OF YEAR CALCULATION FUNCTION
================================================================================
*/

int calculate_day_of_year_position(int day_value, int month_value, int year_value) {
    // Initialize day accumulation counter
    int accumulated_days = 0;
    
    // Sum days from all preceding months
    for (int preceding_month = 1; preceding_month < month_value; preceding_month++) {
        accumulated_days += calculate_month_day_count(preceding_month, year_value);
    }
    
    // Add current month day value to accumulated total
    accumulated_days += day_value;
    
    return accumulated_days; // Return calculated day-of-year position
}

/*
================================================================================
PROGRESS INDICATOR DISPLAY FUNCTION
================================================================================
*/

void display_calendar_generation_progress(int current_month, int total_months) {
    // Calculate completion percentage for progress indication
    double completion_percentage = (double(current_month) / total_months) * 100.0;
    
    // Display formatted progress indicator
    cout << "Generation Progress: " << current_month << "/" << total_months 
         << " (" << fixed << setprecision(0) << completion_percentage << "%)" << endl;
    
    // Generate visual progress bar representation
    int progress_bar_length = 30;
    int completed_segments = (current_month * progress_bar_length) / total_months;
    
    cout << "Progress Bar: [";
    for (int segment_counter = 0; segment_counter < progress_bar_length; segment_counter++) {
        if (segment_counter < completed_segments) {
            cout << "="; // Completed segment indicator
        } else {
            cout << " "; // Remaining segment indicator
        }
    }
    cout << "]" << endl;
}