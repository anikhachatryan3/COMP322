#Name: Ani Khachatryan
#Date: 20 April 2020
#Assignment: Lab 4 - Rice, Rice, and Rice

#Bash Script:
#Steps on how to run: 1) compile using: chmod +x launch-philosophers.sh
#                     2) run using: ./launch-philosophers.sh <seats> <position>

#if the user gives more than 2 arguments
if [ $# -gt 2 ] ; then
      echo "Error: too many arguments.";
      exit 1;
fi

program=./dining-p
seats=$1
position=$2

#if there's no number of seats given
if [ -z ${seats} ] ; then
      echo "Error: please provide the number of seats.";
      exit 1;
fi

#if there's no position number given
if [ -z ${position} ] ; then
      echo "Error: please provide the number of philosophers.";
      exit 1;
fi

#if the position/number of philosophers is a negative number
if [ ${position} -lt 0 ] ; then
      echo "Error: please a provide positive number for number of philosophers."
      exit 1;
fi

#if the number of seats is a negative number
if [ ${seats} -lt 0 ] ; then
      echo "Error: please a provide positive number for number of seats."
      exit 1;
fi

#if there's less seats than philosophers/position given
if [ ${seats} -lt ${position} ] ; then
      echo "Error: not enough seats.";
      exit 1;
fi

#run while the number of cycles is less than or equal to the position number
cycle=1
while [ ${cycle} -le ${position} ] ; do
      ${program} ${seats} ${cycle} &
      echo "Philosopher #${cycle}'s PID is" $!
      cycle=$(( $cycle + 1 ))
done
