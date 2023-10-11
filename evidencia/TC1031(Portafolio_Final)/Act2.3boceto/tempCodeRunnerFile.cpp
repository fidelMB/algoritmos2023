class Date {
    private: 
        string year, month, day, hour; 
    public:
        Date() {
            year = "";
            month = "";
            day = "";
            hour = "";
        }

        Date(string year, string month, string day, string hour) {
            this->year = year;
            this->day = day;
            this->hour = hour;

            if (month == "Jan") {
                this->month = "01";
            }
            else if (month == "Feb") {
                this->month = "02";
            }
            else if (month == "Mar") {
                this->month = "03";
            }
            else if (month == "Apr") {
                this->month = "04";
            }
            else if (month == "May") {
                this->month = "05";
            }
            else if (month == "Jun") {
                this->month = "06";
            }
            else if (month == "Jul") {
                this->month = "07";
            }
            else if (month == "Aug") {
                this->month = "08";
            }
            else if (month == "Sep") {
                this->month = "09";
            }
            else if (month == "Oct") {
                this->month = "10";
            }
            else if (month == "Nov") {
                this->month = "11";
            }
            else if (month == "Dec") {
                this->month = "12";
            }
            
        }

        void setYear(string year) {
            
        }

        string getYear() {
            return year;
        }

        void setMonth(string month) {
            if (month == "Jan") {
                this->month = "01";
            }
            else if (month == "Feb") {
                this->month = "02";
            }
            else if (month == "Mar") {
                this->month = "03";
            }
            else if (month == "Apr") {
                this->month = "04";
            }
            else if (month == "May") {
                this->month = "05";
            }
            else if (month == "Jun") {
                this->month = "06";
            }
            else if (month == "Jul") {
                this->month = "07";
            }
            else if (month == "Aug") {
                this->month = "08";
            }
            else if (month == "Sep") {
                this->month = "09";
            }
            else if (month == "Oct") {
                this->month = "10";
            }
            else if (month == "Nov") {
                this->month = "11";
            }
            else if (month == "Dec") {
                this->month = "12";
            }
        }

        string getMonth() {
            return month;
        }

        void setDay(string day) {
            this->day = day;
        }

        string getDay() {
            return day;
        }

        void setHour(string hour) {
            this->hour = hour;
        }

        string getHour() {
            return hour;
        }

        void setHour(string hour) {
            this->hour = hour;
        }

        string getHour() {
            return hour;
        }
        
        bool operator>=(const Date& other) const {
            if (year != other.year) {
                return year > other.year;
            }
            if (month != other.month) {
                return month > other.month;
            }
            if (day != other.day) {
                return day > other.day;
            }
            if (hour != other.hour) {
                return hour > other.hour;
            }
        }

};
