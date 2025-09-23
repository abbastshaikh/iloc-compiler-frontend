#include <Scanner.hpp>
#include <Parser.hpp>
#include <iostream>
#include <cstring>

void help () {
   std::cout << "Usage: 412fe [-h] [-s <filename>] [-p <filename>] [-r <filename>] [<filename>]" << std::endl;
   std::cout << "Options:" << std::endl;
   std::cout << "   -h: Print this help menu." << std::endl;
   std::cout << "   -s <filename>: Scan <filename> and print all scanned tokens." << std::endl;
   std::cout << "   -p <filename>: Scan and parse <filename> and print number of parsed operations." << std::endl;
   std::cout << "   -r <filename>: Scan and parse <filename> and print the intermediate representation." << std::endl;
   std::cout << "   <filename>: Scan and parse <filename> and print number of parsed operations." << std::endl;
}

void printError (std::string message) {
   std::cerr << "ERROR: " << message << std::endl;
   std::cout << std::endl;
   help();
}

void scan (std::string filename) {

   try {
      Scanner scanner (filename);

      int line = 1;
      Token token = scanner.nextToken();    
      while (token.category != Category::CAT_EOF) {
         if (token.category != Category::CAT_INVAL) {
            std::cout << line << ": " << token.toString() << std::endl;
            if (token.category == Category::CAT_EOL){
               line ++;
            }
         }
         token = scanner.nextToken();
      }
      std::cout << line << ": " << token.toString() << std::endl;
   } catch (FileNotFoundException& e) {
      printError(e.what());
   }
}

void parse (std::string filename) {

   try {
      Scanner scanner (filename);

      try {
         Parser parser (scanner);
         InternalRepresentation rep = parser.parse();
         std::cout << "Parse succeeded. Processed " << rep.count << " operations." << std::endl;
      } catch (...) {
         std::cerr << "Parse found errors." << std::endl;
      }
   } catch (FileNotFoundException& e) {
      printError(e.what());
   }
}

void printIR (std::string filename) {

   try {
      Scanner scanner (filename);

      try {
         Parser parser (scanner);
         InternalRepresentation rep = parser.parse();
         rep.operations->print();
      } catch (...) {
         std::cerr << "Due to syntax errors, run terminates." << std::endl;
      }
   } catch (FileNotFoundException& e) {
      printError(e.what());
   }
}

int main (int argc, char *argv[]) {

   if (argc < 2) {
      printError("Must provide command line arguments.");
      return -1;
   }

   if (!strcmp(argv[1], "-h")){
      help();
   } else if (!strcmp(argv[1], "-s")){
      if (argc == 2) {
         printError("Expected filename after -s.");
         return -1;
      }
      scan(argv[2]);
   } else if (!strcmp(argv[1], "-p")){
      if (argc == 2) {
         printError("Expected filename after -p.");
         return -1;
      }
      parse(argv[2]);
   } else if (!strcmp(argv[1], "-r")){
      if (argc == 2) {
         printError("Expected filename after -r.");
         return -1;
      }
      printIR(argv[2]);
   } else if (argv[1][0] == '-'){
      if (argc == 2) {
         printError("Option " + std::string(argv[1]) + " not recognized.");
         return -1;
      }
      printIR(argv[2]);
   } else {
      parse(argv[1]);
   }

   return 0;
}
