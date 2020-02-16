
README Document:

01/25/2020: I created the Lab0 assignment in GitHub. I created a .gitignore file, which is the 
            only thing that is available so far.
            Status: not working; just created.

01/29/2020: I wrote the inputFile.txt that contains the binary numbers that will be read and 
            converted. I also wrote the main method that only prints the header ("Original, 
            ASCII, etc.") and underlined portions so far.
            Status: not working because I have not worked on it yet

02/04/2020: I worked on the Lab0 assignment at the tutoring center, and I managed to create a 
            method that will read the file and store the content in it as a char array. I also 
            changed a few small things in the main method, such as deleting the T. Error, and 
            calling the readFile method. I also created a makefile so the code can be compiled 
            without having to type the entire commands. I will work on the project more later on.
            Status: not working yet.

02/06/2020: I worked on the lab today, and got the code to actually be padded with zeros 
            instead of just printing the zeros. I also converted the char array to an int array 
            and saved the values of the char array in it. I also somehow added a .vscode file, 
            but I am not sure how so I made a .gitignore to ignore it. I also added more to the 
            makefile; I added REM to remove/delete the Lab0 and Lab0.o files.
            Status: not complete yet but getting there.

02/06/2020: I worked on the code some more, and got it to print the correct ascii characters and 
            the correct decimal number. After figuring that out, I broke up the code that was 
            all written in the readFile method into their own methods. I am also adding my logs 
            here now because I forgot to add them completely.
            Status: works but I have not added the GitHub URL yet.

02/08/2020: I realized that I was not using read() or argc or argv in my code like I was supposed 
            to, so I rewrote and rearranged a couple areas of my code to use read(), argc, and 
            argv. I also separated some parts of my code that were being called in the readFile 
            method. I also added the if statements into the main to check if user is giving a file 
            or just regular inputs.
            Status: completed
            
02/15/2020: I made the code print nothing but the headers and the lines under if the user gives no 
            actual inputs after the '-'. I also added a few more checks to make sure to error out 
            if the given input is invalid.
            Status: completed
