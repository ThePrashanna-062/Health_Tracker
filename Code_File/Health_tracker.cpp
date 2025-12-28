#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
using namespace std;

class pin
{
private:
    string initialpin;
    string newpin;
    int attempts = 3;

public:
    pin()
    {
        initialpin = "open";
    }

    void check()
    {
        while (attempts >= 0)
        {
            string t;
            cout << "Enter 'open' to continue: ";
            cin >> t;
            if (t == initialpin && attempts != 0)
            {
                cout << "Access granted" << endl;
                break;
            }
            else if (attempts == 0)
            {
                cout << "Too many incorrect attempts \nAccess denied.......";
                exit(-1);
            }
            attempts--;
            cout << attempts << " Attempts are left" << endl;
        }
    }

    void authentication()
    {
        attempts = 3;
        string extract; // to check if file is empty
        ifstream file("pin.txt");
        if (file.is_open())
        {
            getline(file, extract);
            file.close();
        }
        if (extract.empty())
        {
            initialpin = "open";
        }
        else
        {
            initialpin = extract;
        }
        while (attempts >= 0)
        {
            string temp;
            cout << "Enter your 'old' password: ";
            cin >> temp;
            if (temp == initialpin && attempts != 0)
            {
                cout << "Enter your 'new' password: ";
                cin >> newpin;

                ofstream file("pin.txt");
                if (file.is_open())
                {
                    file << newpin << endl;
                    file.close();
                    cout << "Password changed and saved successfully\n";
                }
                else
                {
                    cout << "Failed to save password\n";
                }
                newcheck();
                break;
            }
            else if (attempts == 0)
            {
                cout << "Too many incorrect attempts \nAccess denied.......";
                exit(0);
            }
            attempts--;
            cout << attempts << " Attempts are left" << endl;
        }
    }

    void newcheck()
    {
        attempts = 3;
        string temp;
        string checkpin;
        ifstream file("pin.txt");
        if (file.is_open())
        {
            getline(file, checkpin);
            file.close();
        }
        else
        {
            cout << "Unknown error occurred\n";
        }
        while (attempts >= 0)
        {
            cout << "Enter your password: ";
            cin >> temp;
            if (checkpin == temp && attempts != 0)
            {
                cout << "Access granted" << endl;
                break;
            }
            else if (attempts == 0)
            {
                cout << "Too many incorrect attempts \nAccess denied....";
                exit(-1);
            }
            attempts--;
            cout << attempts << " Attempts are left" << endl;
        }
    }
};

class person
{
protected:
    string name = "Empty";
    int age = 0;
    float height = 0;

public:
    void inputpersondata()
    {
        cout << "Enter your name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter your age: ";
        cin >> age;
        cout << "Enter your height in cm: ";
        cin >> height;
        try
        {
            if (age < 0 || height < 0)
            {
                throw invalid_argument("Invalid age or height");
            }
        }
        catch (const invalid_argument &e)
        {
            cout << "Error: Invalid input detected." << endl;
            return;
        }
        set_in_file();
    }

    void set_in_file()
    {
        ofstream file("person.txt");
        if (file.is_open())
        {
            file << name << endl;
            file << age << endl;
            file << height << endl;
            file.close();
        }
        else
        {
            cout << "Failed to open file for writing." << endl;
        }
    }

    bool is_person_data_exists()
    {
        ifstream file("person.txt");
        if (!file.is_open())
            return false;
        string temp;
        getline(file, temp);
        file.close();
        return !temp.empty();
    }
};

class HealthData : public person
{
protected:
    string date;
    string timeStr;
    float water_intake = 0;
    float weight = 0;
    float sleep = 0;
    int BP_systolic = 0;
    int BP_diastolic = 0;
    int steps = 0;
    float BMI = 0;
    float calories = 0;
    float BMR = 0;

public:
    void inputdata()
    {
        if (!is_person_data_exists())
        {
            cout << "Personal data not found. Please enter your personal information first." << endl;
            inputpersondata();
        }

        ifstream filep("person.txt");
        if (filep.is_open())
        {
            getline(filep, name);
            string agetemp, heighttemp;
            getline(filep, agetemp);
            getline(filep, heighttemp);
            age = stoi(agetemp);
            height = stof(heighttemp);
            filep.close();
        }
        else
        {
            cout << "Failed to open person file." << endl;
            return;
        }

        cout << "Enter Date (YYYY-MM-DD): ";
        cin >> date;
        cout << "Enter Time (HH:MM): ";
        cin >> timeStr;
        cout << "Enter your water intake in litres: ";
        cin >> water_intake;
        cout << "Enter your weight in kg: ";
        cin >> weight;
        cout << "Enter your sleep in hours: ";
        cin >> sleep;
        cout << "Enter your BP_systolic: ";
        cin >> BP_systolic;
        cout << "Enter your BP_diastolic: ";
        cin >> BP_diastolic;
        cout << "Enter your steps: ";
        cin >> steps;

        try
        {
            if (water_intake < 0 || weight < 0 || sleep < 0 || BP_systolic < 0 || BP_diastolic < 0 || steps < 0)
            {
                throw invalid_argument("Negative values are not allowed.");
            }
        }
        catch (const invalid_argument &e)
        {
            cout << "Error: Negative values are not allowed." << endl;
            return;
        }

        calculations();
    }

    void calculations()
    {
        BMI = weight / ((height / 100) * (height / 100));
        BMR = 10 * weight + 6.25 * height - 5 * age + 5;
        calories = BMR * 1.2;
        set_to_file();
    }

    void showdata()
    {
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "Height: " << height << " cm" << endl;
        cout << "Water Intake: " << water_intake << " litres" << endl;
        cout << "Weight: " << weight << " kg" << endl;
        cout << "Sleep: " << sleep << " hours" << endl;
        cout << "Blood Pressure: " << BP_systolic << "/" << BP_diastolic << endl;
        cout << "Steps: " << steps << endl;
        cout << "BMI: " << BMI << endl;
        cout << "BMR (Assuming minimal activity): " << BMR << " kcal/day" << endl;
        cout << "Approximate calories Burned: " << calories << endl;
    }

    void set_to_file()
    {
        // Append to individual files (optional)
        ofstream file("water.txt", ios::app);
        if (file.is_open()) { file << water_intake << endl; file.close(); }
        else cout << "Failed to open water.txt\n";

        ofstream file1("weight.txt", ios::app);
        if (file1.is_open()) { file1 << weight << endl; file1.close(); }
        else cout << "Failed to open weight.txt\n";

        ofstream file2("sleep.txt", ios::app);
        if (file2.is_open()) { file2 << sleep << endl; file2.close(); }
        else cout << "Failed to open sleep.txt\n";

        ofstream file3("BP.txt", ios::app);
        if (file3.is_open()) { file3 << BP_systolic << "/" << BP_diastolic << endl; file3.close(); }
        else cout << "Failed to open BP.txt\n";

        ofstream file4("BMI.txt", ios::app);
        if (file4.is_open()) { file4 << BMI << endl; file4.close(); }
        else cout << "Failed to open BMI.txt\n";

        ofstream file5("calories.txt", ios::app);
        if (file5.is_open()) { file5 << calories << endl; file5.close(); }
        else cout << "Failed to open calories.txt\n";

        // Write all data with date/time to history.txt in table format
        ofstream fileh("history.txt", ios::app);
        if (fileh.is_open())
        {
            fileh << date << " | " << timeStr << " | "
                  << water_intake << " L  | "
                  << weight << " kg   | "
                  << sleep << " hr  | "
                  << BP_systolic << "/" << BP_diastolic << "   | "
                  << BMI << "  | "
                  << calories << " kcal"
                  << endl;
            fileh.close();
        }
        else
        {
            cout << "Failed to open history.txt\n";
        }
    }

    void history()
    {
        cout << "Name: " << name << endl;
        cout << "\n...Displaying History...\n\n";
        ifstream file("history.txt");
        if (file.is_open())
        {
            string line;
            cout << "--------------------------------------------------------------------------------------------\n";
            cout << "Date       | Time  | Water | Weight | Sleep | Pressure | BMI  | Calories\n";
            cout << "--------------------------------------------------------------------------------------------\n";

            while (getline(file, line))
            {
                cout << line << endl;
            }

            cout << "--------------------------------------------------------------------------------------------\n";
            file.close();
        }
        else
        {
            cout << "No history found or failed to open history.txt\n";
        }
    }
};

class Goal : public person
{
private:
    float waterGoal;
    float sleepGoal;
    float weightGoal;

public:
    Goal()
    {
        float ht = 0;
        ifstream file("person.txt");
        if (file.is_open())
        {
            string line;
            getline(file, line); // name
            getline(file, line); // age
            while (getline(file, line)) // height
            {
                ht = stof(line);
            }
            file.close();
        }
        else
        {
            cout << "Failed to open person file." << endl;
        }
        waterGoal = 3;
        sleepGoal = 8;
        weightGoal = 22 * (ht / 100) * (ht / 100);
    }

    void initializeGoalFile()
    {
        ifstream file("goal.txt");
        if (!file.is_open())
        {
            ofstream newfile("goal.txt");
            if (newfile.is_open())
            {
                newfile << waterGoal << " " << sleepGoal << " " << weightGoal << endl;
                newfile.close();
            }
        }
        else
        {
            file.close();
        }
    }

    void loadGoalFromFile()
    {
        ifstream file("goal.txt");
        if (file.is_open())
        {
            file >> waterGoal >> sleepGoal >> weightGoal;
            file.close();
        }
    }

    void showGoal()
    {
        cout << "-----Current Goals-----\n";
        cout << "Water Intake: " << waterGoal << " L\n";
        cout << "Sleep: " << sleepGoal << " hr\n";
        if (weightGoal == 0)
        {
            cout << "Weight goal can't be set. Enter your data first." << endl;
            inputpersondata();
        }
        else
        {
            cout << "Weight: " << weightGoal << " kg\n";
        }
    }

    void changeGoal()
    {
        cout << "Enter new water intake goal (litres): ";
        cin >> waterGoal;
        cout << "Enter new sleep goal (hours): ";
        cin >> sleepGoal;
        cout << "Enter new weight goal (kg): ";
        cin >> weightGoal;

        ofstream file("goal.txt");
        if (file.is_open())
        {
            file << waterGoal << " " << sleepGoal << " " << weightGoal << endl;
            file.close();
            cout << "Goals updated successfully!\n";
        }
    }
};

class Quote
{
private:
    string quoteOfDay;

public:
    void setQuote()
    {
        string quotes[10] = {
            "Push yourself, because no one else is going to do it for you.",
            "Success doesn't just find you. You have to go out and get it.",
            "Great things never come from comfort zones.",
            "Dream it. Wish it. Do it.",
            "Don't stop when you're tired. Stop when you're done.",
            "Work hard in silence, let success make the noise.",
            "The key to success is to focus on goals, not obstacles.",
            "Discipline is the bridge between goals and accomplishment.",
            "Start where you are. Use what you have. Do what you can.",
            "The harder you work for something, the greater you'll feel when you achieve it."};

        srand(time(0));
        int index = rand() % 10;
        quoteOfDay = quotes[index];
    }

    void displayQuote()
    {
        cout << "\n\t\t------ Quote of the Day ------\n";
        cout << quoteOfDay << "\n\n";
    }
};

void clearAllDataFiles()
{
    const char *files[] = {
        "history.txt",
        "water.txt",
        "weight.txt",
        "sleep.txt",
        "BP.txt",
        "BMI.txt",
        "calories.txt",
        "person.txt",
        "pin.txt",
        "goal.txt"};
    int n = sizeof(files) / sizeof(files[0]);

    for (int i = 0; i < n; i++)
    {
        ofstream file(files[i], ios::trunc);
        if (file.is_open())
        {
            file.close();
        }
        else
        {
            cout << "Failed to clear " << files[i] << endl;
        }
    }
    cout << "All data files cleared successfully!\n";
}

void finalcheck()
{
    pin pass;
    string extract;
    ifstream file("pin.txt");
    if (file.is_open())
    {
        getline(file, extract);
        file.close();
    }

    if (extract.empty())
    {
        pass.check();
    }
    else
    {
        pass.newcheck();
    }
}

int main()
{
    finalcheck();
    pin p;
    HealthData data_per;
    Goal goal;
    Quote quote;
    int choice;

    goal.initializeGoalFile();
    goal.loadGoalFromFile();
    quote.setQuote();

    do
    {
        cout << "\n\n";
        cout << "\t 'WELCOME TO HEALTH TRACKING SYSTEM'\n";
        quote.displayQuote();
        cout << "\t1. Data\n";
        cout << "\t2. Display history\n";
        cout << "\t3. Personal goals\n";
        cout << "\t4. Change password\n";
        cout << "\t5. Clear all stored data\n";
        cout << "\t6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            int achoice;
            cout << "\t1. Enter data\n";
            cout << "\t2. Show data\n";
            cout << "Enter choice: ";
            cin >> achoice;
            switch (achoice)
            {
            case 1:
                cout << "\n";
                data_per.inputdata();
                break;
            case 2:
                cout << "\n";
                data_per.showdata();
                break;
            default:
                cout << "Incorrect option" << endl;
                break;
            }
            break;
        }
        case 2:
            cout << "\n";
            data_per.history();
            break;

        case 3:
        {
            int gchoice;
            cout << "\t1. Show goal\n";
            cout << "\t2. Change goal\n";
            cout << "Enter choice: ";
            cin >> gchoice;
            switch (gchoice)
            {
            case 1:
                goal.showGoal();
                break;
            case 2:
                goal.changeGoal();
                break;
            default:
                cout << "Incorrect option" << endl;
                break;
            }
            break;
        }
        case 4:
            cout << "\n";
            p.authentication();
            break;

        case 5:
            cout << "\nAuthorization is required" << endl;
            finalcheck();
            cout << "Are you sure you want to clear all stored data? (y/n): ";
            char confirm;
            cin >> confirm;

            if (confirm == 'y' || confirm == 'Y')
            {
                clearAllDataFiles();
            }
            else
            {
                cout << "Clear data cancelled." << endl;
            }
            break;

        case 6:
            cout << "\nExiting the program.......\n";
            exit(0);

        default:
            cout << "Incorrect option" << endl;
            cout << "\tChoose a correct option" << endl;
            break;
        }
        cout << "\n";
    } while (choice != 6);

    return 0;
}
