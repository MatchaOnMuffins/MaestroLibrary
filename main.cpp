#include <iostream>
#include "lib/libMaestroControl.h"
#include <sstream>
#include <string>
#include "lib/webserver.h"
#include "lib/Socket.h"

using namespace std;

string serialPort;
int channel1;
int channel2;
double delay1 = 0.1;
double delay2 = 0.5;
int steps1 = 360;
int steps2 = 72;
// string par[7] = {"serialPort", "channel1", "channel2", "delay1", "delay2", "steps1", "steps2"};

void print(const string &s) {
    cout << s << endl;
}

/*
void Request_Handler(webserver::http_request *r) {
    Socket s = *(r->s_);

    std::string title;
    std::string body;
    std::string bgcolor = "#ffffff";
    std::string links =
            "<p><a href='rchat.fun'>forms</a> ";

    if (r->path_ == "/") {
        title = "MaestroControl";
        body += "<!DOCTYPE html>\n"
                "<html lang=\"en\">\n"
                "<head>\n"
                "    <meta charset=\"UTF-8\">\n"
                "    <title>MaestroControl</title>\n"
                "\n"
                "    <style>\n"
                "        body {\n"
                "            background-color: #f5f5f5;\n"
                "        }\n"
                "\n"
                "        input {\n"
                "            border: none;\n"
                "            border-bottom: 2px solid #ccc;\n"
                "            background-color: #f5f5f5;\n"
                "            font-size: 1.5em;\n"
                "            font-family: 'Roboto', sans-serif;\n"
                "            font-weight: 300;\n"
                "            color: #333;\n"
                "        }\n"
                "\n"
                "        select {\n"
                "            border: none;\n"
                "            border-bottom: 2px solid #ccc;\n"
                "            background-color: #f5f5f5;\n"
                "            font-size: 1.5em;\n"
                "            font-family: 'Roboto', sans-serif;\n"
                "            font-weight: 300;\n"
                "            color: #333;\n"
                "        }\n"
                "\n"
                "        .control-label {\n"
                "            font-family: \"Comic Sans MS\", cursive, sans-serif;\n"
                "            font-size: 1.5em;\n"
                "            color: black;\n"
                "            cursor: default;\n"
                "        }\n"
                "    </style>\n"
                "</head>\n"
                "<body>\n"
                "<div style=\"text-align: left\">\n"
                "    <form action=\"/\" autocomplete=\"off\">\n"
                "        <label class=\"control-label\" for=\"port\">Serial Port</label>\n"
                "        <br>\n"
                "        <br>\n"
                "        <select id=\"port\" name=\"Serial Port\">\n"
                "            <option value=\"COM1\">COM1</option>\n"
                "            <option value=\"COM2\">COM2</option>\n"
                "            <option value=\"COM3\">COM3</option>\n"
                "            <option value=\"COM4\">COM4</option>\n"
                "            <option value=\"COM5\">COM5</option>\n"
                "            <option value=\"COM6\">COM6</option>\n"
                "            <option value=\"COM7\">COM7</option>\n"
                "            <option value=\"COM8\">COM8</option>\n"
                "            <option value=\"COM9\">COM9</option>\n"
                "            <option value=\"COM10\">COM10</option>\n"
                "        </select>\n"
                "        <br>\n"
                "        <br>\n"
                "        <label class=\"control-label\" for=\"channel1\">Serial Port</label>\n"
                "        <br>\n"
                "        <br>\n"
                "        <input id=\"channel1\" type=\"number\" name=\"channel1\" min=\"0\" max=\"23\" placeholder=\"0\" value=\"0\">\n"
                "        <br>\n"
                "        <br>\n"
                "        <label class=\"control-label\" for=\"channel2\">Serial Port2</label>\n"
                "        <br>\n"
                "        <br>\n"
                "        <input id=\"channel2\" type=\"number\" name=\"channel2\" min=\"0\" max=\"23\" placeholder=\"5\" value=\"5\">\n"
                "        <br>\n"
                "        <br>\n"
                "        <label class=\"control-label\" for=\"delay1\">Servo 1 Delay time</label>\n"
                "        <br>\n"
                "        <br>\n"
                "        <input id=\"delay1\" type=\"number\" name=\"delay1\" step=\"0.05\" min=\"0\" max=\"0.5\" placeholder=\"0.1\" value=\"0.1\">\n"
                "        <br>\n"
                "        <br>\n"
                "        <label class=\"control-label\" for=\"delay2\">Servo 1 Delay time</label>\n"
                "        <br>\n"
                "        <br>\n"
                "        <input id=\"delay2\" type=\"number\" name=\"delay2\" step=\"0.1\" min=\"0\" max=\"0.5\" placeholder=\"0.5\" value=\"0.5\">\n"
                "        <br>\n"
                "        <br>\n"
                "        <label class=\"control-label\" for=\"steps1\">Servo 1 total step count</label>\n"
                "        <br>\n"
                "        <br>\n"
                "        <input id=\"steps1\" type=\"number\" name=\"steps1\" step=\"10\" min=\"10\" max=\"720\" placeholder=\"360\" value=\"20\">\n"
                "        <br>\n"
                "        <br>\n"
                "        <label class=\"control-label\" for=\"steps2\">Servo 2 total step count</label>\n"
                "        <br>\n"
                "        <br>\n"
                "        <input id=\"steps2\" type=\"number\" name=\"steps2\" step=\"5\" min=\"10\" max=\"100\" placeholder=\"70\" value=\"20\">\n"
                "        <br>\n"
                "        <br>\n"
                "        <input type=\"submit\" value=\"Submit\">\n"
                "    </form>\n"
                "</div>\n"
                "</body>\n"
                "</html>";

        int j = 0;
        for (std::map<std::string, std::string>::const_iterator i = r->params_.begin();
             i != r->params_.end();
             i++) {

            //body += "<br>" + i->first + " = " + i->second;

            //std::cout << (std::string) (i->first) << "=" << (std::string) (i->second) << std::endl;
            //params[i]=  ((std::string) (i->second));
            string fun = (string) (i->second);
            //cout << fun << endl;

            par[j] = fun;
            j++;
            //params[i] = "yeet";
        }
        serialPort = par[0];
        channel1 = stoi(par[1]);
        channel2 = stoi(par[2]);
        delay1 = stod(par[3]);
        delay2 = stod(par[4]);
        steps1 = stoi(par[5]);
        steps2 = stoi(par[6]);



        // servoControl(serialPort.c_str(), channel1, channel2, delay1, steps1, delay2, steps2);
        //body += "<hr>" + links;
        cout << "params: " << par[0] << " " << par[1] << " " << par[2] << " " << par[3] << " " << par[4] << " "
             << par[5] << " " << par[6] << " end" << endl;
        servoControl(serialPort.c_str(), channel1, channel2, delay1, steps1, delay2, steps2);
    } else {
        r->status_ = "404 Not Found";
        title = "Wrong URL";
        body = "<h1>Wrong URL</h1>";
        body += "Path is : &gt;" + r->path_ + "&lt;";
    }

    r->answer_ = "<html><head><title>";
    r->answer_ += title;
    r->answer_ += "</title></head><body bgcolor='" + bgcolor + "'>";
    r->answer_ += body;
    r->answer_ += "</body></html>";
}*/

void prompts() {
    cout << "Welcome to MaestroControl!" << endl;
    cout
            << "Please enter the serial port of your Maestro (this can be found by running 'ls /dev/cu.usbmodem* ' in the terminal): ";
    cin >> serialPort;
    cout << "Please enter the channel number for servo 1: ";
    cin >> channel1;
    cout << "Please enter the channel number for servo 2: ";
    cin >> channel2;
    getchar();
    cout << "Please enter the delay between each move for servo 1 in seconds: (default is 0.1 seconds)";


    string input1;
    getline(cin, input1);
    if (!input1.empty()) {
        istringstream stream(input1);
        stream >> delay1;
    }
    cout << "delay1" << delay1;

    cout << "Please enter the delay between each move for servo 2 in seconds: (default is 0.5 seconds)";


    string input2;
    getline(cin, input2);
    if (!input2.empty()) {
        istringstream stream(input2);
        stream >> delay2;
    }

    cout << "Please enter the number of steps for servo 1 to move: (default is 360 steps)";


    string input_step1;
    getline(cin, input_step1);
    if (!input_step1.empty()) {
        istringstream stream(input_step1);
        stream >> steps1;
    }

    cout << "Please enter the number of steps for servo 2 to move: (default is 72 steps)";


    string input_step2;
    getline(cin, input_step2);
    if (!input_step2.empty()) {
        istringstream stream(input_step2);
        stream >> steps2;
    }
    cout << "The current serial port is: " << serialPort << endl;
    cout << "The current channel number for servo 1 is: " << channel1 << endl;
    cout << "The current channel number for servo 2 is: " << channel2 << endl;
    cout << "The current delay between each move for servo 1 is: " << delay1 << endl;
    cout << "The current delay between each move for servo 2 is: " << delay2 << endl;
    cout << "The current number of steps for servo 1 to move is: " << steps1 << endl;
    cout << "The current number of steps for servo 2 to move is: " << steps2 << endl;
    cout << "Press enter to continue..." << std::endl;
    getchar();
}


int main() {
    //cout << "Listening on localhost:80!" << endl;
    //webserver(80, Request_Handler);
    //cout << "Exiting..." << endl;
    //getchar();

    prompts();
    servoControl(serialPort.c_str(), channel1, channel2, delay1, steps1, delay2, steps2);
    // servoControl("/dev/cu.usbmodem001033281", 0, 5, 0.05, 100, 0.5, 72);
    return 0;
}


