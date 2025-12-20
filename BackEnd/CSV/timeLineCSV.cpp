#include "timeLineCSV.h"
using namespace std;
namespace timeLineCSV
{
    string PATH = Utils::GetOriginFolder();
    void updateLoanNumber(int loanNb)
    {
        ifstream read(PATH + "/BackEnd/Data/timeLine.csv");
        ofstream copy(PATH + "/BackEnd/Data/copy.csv");

        string line;
        int pos;

        getline(read, line);
        copy << line << '\n';

        getline(read, line);
        copy << line << '\n';

        getline(read, line);
        copy << line << '\n';

        copy << loanNb << '\n';

        read.close();
        copy.close();
        string path = PATH + "/BackEnd/Data/timeLine.csv";
        string path2 = PATH + "/BackEnd/Data/copy.csv";
        remove(path.c_str());
        rename(path2.c_str(), path.c_str());
    }

    void addNewMonth(int interestRate, int cusNb, int empNb, int loanNb)
    {
        // in timeLineCSV :
        // first line interest rate evolution over the last 6 months (/100)% || evolução da taxa de juros nos últimos 6 meses (/100)%
        // second line Accounts number evolution over the last 6 months || evolução do número de clientes nos últimos 6 meses
        // third line employees number evolution over the last 6 months || evolução do número de funcionários nos últimos 6 meses

        ifstream read(PATH + "/BackEnd/Data/timeLine.csv");
        ofstream copy(PATH + "/BackEnd/Data/copy.csv");
        string arr[3] = {to_string(interestRate), to_string(cusNb), to_string(empNb)};
        string line;
        int pos;
        for (int k = 0; k < 3; k++)
        {

            getline(read, line);
            for (int i = 0; i < line.length(); i++)
            {
                if (line[i] == ',')
                {
                    pos = i;
                    break;
                }
            }
            string rest = line.substr(pos + 1);
            copy << rest;
            copy << ',';
            copy << arr[k];
            copy << '\n';
        }
        read.close();
        copy.close();
        string path = PATH + "/BackEnd/Data/timeLine.csv";
        string path2 = PATH + "/BackEnd/Data/copy.csv";
        remove(path.c_str());
        rename(path2.c_str(), path.c_str());

        updateLoanNumber(loanNb);
    }

    void updateInterestRate(int intRate)
    {
        ifstream read(PATH + "/BackEnd/Data/timeLine.csv");
        ofstream copy(PATH + "/BackEnd/Data/copy.csv");

        string line;
        int pos;
        getline(read, line);
        for (int i = line.length() - 1; i > -1; i--)
        {
            if (line[i] == ',')
            {
                pos = i;
                break;
            }
        }
        string rest = line.substr(0, pos + 1);
        copy << rest;
        copy << intRate;
        copy << '\n';

        getline(read, line);
        copy << line << '\n';

        getline(read, line);
        copy << line << '\n';

        getline(read, line);
        copy << line << '\n';

        read.close();
        copy.close();
        string path = PATH + "/BackEnd/Data/timeLine.csv";
        string path2 = PATH + "/BackEnd/Data/copy.csv";
        remove(path.c_str());
        rename(path2.c_str(), path.c_str());
    }

    void updateAccountNumber(int cusNb)
    {
        ifstream read(PATH + "/BackEnd/Data/timeLine.csv");
        ofstream copy(PATH + "/BackEnd/Data/copy.csv");

        string line;
        int pos;

        getline(read, line);
        copy << line << '\n';

        getline(read, line);
        for (int i = line.length() - 1; i > -1; i--)
        {
            if (line[i] == ',')
            {
                pos = i;
                break;
            }
        }
        string rest = line.substr(0, pos + 1);
        copy << rest;
        copy << cusNb;
        copy << '\n';

        getline(read, line);
        copy << line << '\n';
        getline(read, line);
        copy << line << '\n';

        read.close();
        copy.close();
        string path = PATH + "/BackEnd/Data/timeLine.csv";
        string path2 = PATH + "/BackEnd/Data/copy.csv";
        remove(path.c_str());
        rename(path2.c_str(), path.c_str());
    }

    void updateEmployeeNumber(int empNb)
    {
        ifstream read(PATH + "/BackEnd/Data/timeLine.csv");
        ofstream copy(PATH + "/BackEnd/Data/copy.csv");

        string line;
        int pos;

        getline(read, line);
        copy << line << '\n';

        getline(read, line);
        copy << line << '\n';

        getline(read, line);
        for (int i = line.length() - 1; i > -1; i--)
        {
            if (line[i] == ',')
            {
                pos = i;
                break;
            }
        }
        string rest = line.substr(0, pos + 1);
        copy << rest;
        copy << empNb;
        copy << '\n';

        getline(read, line);
        copy << line << '\n';

        read.close();
        copy.close();
        string path = PATH + "/BackEnd/Data/timeLine.csv";
        string path2 = PATH + "/BackEnd/Data/copy.csv";
        remove(path.c_str());
        rename(path2.c_str(), path.c_str());
    }

    string stringifyInterestRateAsArray()
    {
        ifstream read(PATH + "/BackEnd/Data/timeLine.csv");
        string line;
        getline(read, line);
        read.close();
        return "[" + line + "]";
    }

    string stringifyAccountsNumberAsArray()
    {
        ifstream read(PATH + "/BackEnd/Data/timeLine.csv");
        string line;
        getline(read, line);
        getline(read, line);
        read.close();
        return "[" + line + "]";
    }

    string stringifyEmployeesNumberAsArray()
    {
        ifstream read(PATH + "/BackEnd/Data/timeLine.csv");
        string line;
        getline(read, line);
        getline(read, line);
        getline(read, line);
        read.close();
        return "[" + line + "]";
    }

    string getlastMonthInterestRate()
    {
        ifstream read(PATH + "/BackEnd/Data/timeLine.csv");
        string line, res = "";
        int acc = 0;
        int firstPos, lastPos;
        getline(read, line);
        for (int i = line.length() - 1; i > -1; i--)
        {
            if (line[i] == ',')
            {
                acc++;
                if (acc == 1)
                {
                    lastPos = i;
                }
                else if (acc == 2)
                {
                    firstPos = i;
                    break;
                }
            }
        }
        res = line.substr(firstPos + 1, lastPos - firstPos - 1);

        read.close();
        return res;
    }

    string getlastMonthAccountsNumber()
    {
        ifstream read(PATH + "/BackEnd/Data/timeLine.csv");
        string line, res = "";
        int acc = 0;
        int firstPos, lastPos;
        getline(read, line);
        getline(read, line);
        for (int i = line.length() - 1; i > -1; i--)
        {
            if (line[i] == ',')
            {
                acc++;
                if (acc == 1)
                {
                    lastPos = i;
                }
                else if (acc == 2)
                {
                    firstPos = i;
                    break;
                }
            }
        }
        res = line.substr(firstPos + 1, lastPos - firstPos - 1);

        read.close();
        return res;
    }

    string getlastMonthEmployeesNumber()
    {
        ifstream read(PATH + "/BackEnd/Data/timeLine.csv");
        string line, res = "";
        int acc = 0;
        int firstPos, lastPos;
        getline(read, line);
        getline(read, line);
        getline(read, line);
        for (int i = line.length() - 1; i > -1; i--)
        {
            if (line[i] == ',')
            {
                acc++;
                if (acc == 1)
                {
                    lastPos = i;
                }
                else if (acc == 2)
                {
                    firstPos = i;
                    break;
                }
            }
        }
        res = line.substr(firstPos + 1, lastPos - firstPos - 1);

        read.close();
        return res;
    }

    string getlastMonthLoansNumber()
    {
        ifstream read(PATH + "/BackEnd/Data/timeLine.csv");
        string line;
        int firstPos, lastPos;
        getline(read, line);
        getline(read, line);
        getline(read, line);
        getline(read, line);
        read.close();
        return line;
    }

    // ADDED HERE

    string getCurrentInterestRate()
    {
        ifstream read(PATH + "/BackEnd/Data/timeLine.csv");
        string line, res = "";
        int pos;
        getline(read, line);
        for (int i = line.length() - 1; i > -1; i--)
        {
            if (line[i] == ',')
            {
                pos = i;
                break;
            }
        }
        res = line.substr(pos + 1);

        read.close();
        return res;
    }

    string getCurrentMonthAccountsNumber()
    {
        ifstream read(PATH + "/BackEnd/Data/timeLine.csv");
        string line, res = "";
        int pos;
        getline(read, line);
        getline(read, line);
        for (int i = line.length() - 1; i > -1; i--)
        {
            if (line[i] == ',')
            {
                pos = i;
                break;
            }
        }
        res = line.substr(pos + 1);

        read.close();
        return res;
    }

    string getCurrentMonthEmployeesNumber()
    {
        ifstream read(PATH + "/BackEnd/Data/timeLine.csv");
        string line, res = "";
        int pos;
        getline(read, line);
        getline(read, line);
        getline(read, line);
        for (int i = line.length() - 1; i > -1; i--)
        {
            if (line[i] == ',')
            {
                pos = i;
                break;
            }
        }
        res = line.substr(pos + 1);

        read.close();
        return res;
    }

    // EMD
    string getLastMonth()
    {
        ifstream read(PATH + "/BackEnd/Data/lastMonth.csv");
        string line;
        getline(read, line);

        read.close();
        return line;
    }
    void updateLastMonth(int Month)
    {
        ofstream write(PATH + "/BackEnd/Data/lastMonth.csv", ios::out);
        write << Month << '\n';

        write.close();
    }

}

