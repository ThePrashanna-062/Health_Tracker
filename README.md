# Health Tracking System (C++)

A comprehensive, console-based application designed to help users monitor their daily health metrics, calculate vital body statistics, and track progress toward personal fitness goals.

## 🌟 Key Features

* **Secure Access:** Password-protected entry system with persistent storage (saved in `pin.txt`).
* **Health Analytics:** * **BMI Calculator:** Automatically calculates Body Mass Index based on height and weight.
    * **BMR & Calorie Estimator:** Calculates Basal Metabolic Rate and approximate daily calorie needs.
* **Daily Log Tracking:** Record water intake, sleep hours, blood pressure, and step counts.
* **Data Persistence:** All records are saved across multiple text files, ensuring your history is never lost after closing the program.
* **History View:** A formatted tabular view of all your past health entries.
* **Goal Management:** Set and update targets for weight, sleep, and hydration.
* **Motivational Quotes:** Features a "Quote of the Day" system to keep you inspired.

## 📊 Logic & Calculations

The system uses standard health formulas to provide insights:

1.  **BMI (Body Mass Index):** Calculated as $BMI = \frac{\text{weight (kg)}}{\text{height (m)}^2}$
    

[Image of BMI classification chart]


2.  **BMR (Basal Metabolic Rate):** Uses the Mifflin-St Jeor Equation for a baseline estimate:  
    $BMR = 10 \times \text{weight} + 6.25 \times \text{height} - 5 \times \text{age} + 5$

---

## 🛠 Project Structure

The project is built using Object-Oriented Programming (OOP) principles:

| Class | Responsibility |
| :--- | :--- |
| `pin` | Handles password authentication and security logic. |
| `person` | Base class for user profile (Name, Age, Height). |
| `HealthData` | Manages input, calculation, and history logging. |
| `Goal` | Handles setting and retrieving personal fitness targets. |
| `Quote` | Manages the motivational quote engine. |

---

## 🚀 Getting Started

### Prerequisites
* Any C++ compiler (GCC, Clang, or MSVC).
* Standard C++ libraries (`iostream`, `fstream`, `string`, `ctime`).

### Running the Program
1.  Compile the source code:
    ```bash
    g++ main.cpp -o HealthTracker
    ```
2.  Run the executable:
    ```bash
    ./HealthTracker
    ```
3.  **Default Credentials:** The initial password is `open`.

---

## 📁 File System Layout
The program generates and manages the following files to store data:
* `person.txt`: Your basic profile info.
* `pin.txt`: Your encrypted/saved password.
* `history.txt`: The master log for all health entries.
* `goal.txt`: Your current fitness targets.
* `water.txt`, `weight.txt`, `sleep.txt`, etc.: Individual metric logs.

---

## 🛡 Security Note
If you forget your password, you can manually reset the system by deleting the `pin.txt` file or using the "Clear all stored data" option within the app (requires current password). 