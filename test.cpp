#include "WordCount.h"
#include <sstream>
#include <iostream>
#include "tddFuncs.h"
using namespace std;

int main() {
  cout << "Running tests from: " << __FILE__ << endl;
  
  WordCount w;
  WordCount x;
  WordCount y;
  WordCount z;
  
  cout << "Testing incrWordCount below:" << endl;
  ASSERT_EQUALS(1, w.incrWordCount("Banana"));
  ASSERT_EQUALS(2, w.incrWordCount("#Ba56na/*9na"));
  ASSERT_EQUALS(3, w.incrWordCount("BAna/*9na"));
  ASSERT_EQUALS(1, w.incrWordCount("Bana-na"));
  ASSERT_EQUALS(0, w.incrWordCount("56/*9"));
  ASSERT_EQUALS(0, w.incrWordCount(" "));
  ASSERT_EQUALS(1, w.incrWordCount("B"));
  ASSERT_EQUALS(0, w.incrWordCount("\""));
  ASSERT_EQUALS(0, x.incrWordCount("$%^355"));
  for(size_t i = 0; i < 5; i++)
    z.incrWordCount("apple");
  
 
  cout << "Testing getTotalWords below:" << endl;
  ASSERT_EQUALS(5,w.getTotalWords());
  ASSERT_EQUALS(0,y.getTotalWords());    //empty object
  ASSERT_EQUALS(0,x.getTotalWords());    

  cout << "Testing getNumUniqueWords below:" << endl;
  ASSERT_EQUALS(2, w.getNumUniqueWords());  
  ASSERT_EQUALS(0, x.getNumUniqueWords());  //empty object have 0 unique word
  ASSERT_EQUALS(0, y.getNumUniqueWords());
  ASSERT_EQUALS(0, z.getNumUniqueWords());

  cout << "Testing getWordCount below:" << endl;
  ASSERT_EQUALS(3, w.getWordCount(")B4%6anana"));
  ASSERT_EQUALS(1, w.getWordCount("Bana-na"));
  ASSERT_EQUALS(0, w.getWordCount("2%6Abse(?:>nt"));//bad input not in hashtable
  ASSERT_EQUALS(0, w.getWordCount("()+_"));
  ASSERT_EQUALS(0, w.getWordCount(" "));
  ASSERT_EQUALS(1, w.getWordCount(" B"));
  ASSERT_EQUALS(5, z.getWordCount("apple"));
  ASSERT_EQUALS(0, y.getWordCount("$%^355"));
  ASSERT_EQUALS(0, y.getWordCount(" "));
  ASSERT_EQUALS(0, x.getWordCount("$%^355"));

  cout << "Testing isWordChar below:" << endl;
  ASSERT_TRUE(WordCount::isWordChar('a'));
  ASSERT_TRUE(WordCount::isWordChar('l'));
  ASSERT_TRUE(WordCount::isWordChar('P'));
  ASSERT_TRUE(WordCount::isWordChar('K'));
  ASSERT_TRUE(!WordCount::isWordChar('\''));
  ASSERT_TRUE(!WordCount::isWordChar('0'));
  ASSERT_TRUE(!WordCount::isWordChar('~'));
  ASSERT_TRUE(!WordCount::isWordChar('+'));
  ASSERT_TRUE(!WordCount::isWordChar('}'));
  ASSERT_TRUE(!WordCount::isWordChar(' '));
  ASSERT_TRUE(!WordCount::isWordChar('&'));
  
  cout << "Testing stripWord below:" << endl;
  ASSERT_EQUALS("apple",WordCount::stripWord("apple"));              //normal case with all lower letter
  ASSERT_EQUALS("PineApple",WordCount::stripWord("PineApple"));      //normal case with mix of upper and lower case letter
  ASSERT_EQUALS("Don't",WordCount::stripWord("Don't"));              //normal case with '
  ASSERT_EQUALS("hard-wo-rking",WordCount::stripWord("hard-wo-rking"));//normal case with -
  ASSERT_EQUALS("cat",WordCount::stripWord("0cat"));                 //numbers in front
  ASSERT_EQUALS("apple",WordCount::stripWord("apple8"));             //numbers at the end
  ASSERT_EQUALS("apple",WordCount::stripWord("00890apple"));           //multiple numbers in front
  ASSERT_EQUALS("apple",WordCount::stripWord("apple000"));           //multiple numbers at the end
  ASSERT_EQUALS("apple",WordCount::stripWord("a7p8p24898le"));       //multiple numbers in the middle
  ASSERT_EQUALS("apple",WordCount::stripWord("!-@apple"));           //multiple charater in front
  ASSERT_EQUALS("apple",WordCount::stripWord("apple*%&"));	         //multiple character at the end	
  ASSERT_EQUALS("aPple",WordCount::stripWord("a^*&Pp(le"));	         //multiple character in the middle
  ASSERT_EQUALS("usually",WordCount::stripWord("-usually-"));        //- at beginning and end
  ASSERT_EQUALS("apple",WordCount::stripWord("'apple'"));            //' at beginning and end
  ASSERT_EQUALS("aPple",WordCount::stripWord("'+6'-aP0234p>l,e&^*--\""));  //a mixture of stuff
  ASSERT_EQUALS(" ",WordCount::stripWord("$$---+`*8[[;.?/"));        //strip to empty string

  
  cout << "Testing addAllWords below:" << endl;
  w.addAllWords("");
  w.addAllWords("b");
  w.addAllWords("&##b$@@");
  w.addAllWords("b a c d");
  w.addAllWords("x\ny\nz\n");
  w.addAllWords("$^&x/2# ^%y() 1238Z09");
  w.addAllWords("$^&x/2#\n^%y()\n1238Z09");
  w.addAllWords("$^&x/2#     ^%y()     1238Z09");
  w.addAllWords("$^&x/2#\n\n\n\n\n^%y()\n\n\n\n\n\\1238Z09");
  w.addAllWords("$^&x/2# \n^%y()\n  1238Z09");
  w.addAllWords("bread tastes good");
  w.addAllWords("bread\ntastes\ngood");
  w.addAllWords("123b456r$$#e&ad** t#$as^%t$e(s__ !!~g@o$od%%%%*&56");
  w.addAllWords("123b456r$$#e&ad**\nt#$as^%t$e(s__\n!!~g@o$od%%%%*&56");
  w.addAllWords("123b456r$$#e&ad**     t#$as^%t$e(s__         !!~g@o$od%%%%*&56");
  w.addAllWords("123b456r$$#e&ad**\n\n\n\n\n\n\nt#$as^%t$e(s__\n\n\n\n!!~g@o$od%%%%*&56");
  w.addAllWords("123b456r$$#e&ad**   \n \n \n\n\nt#$as^%t$e(s__    \n\n\n \n \n\n   !!~g@o$od%%%%*&56");

  ASSERT_EQUALS(45, w.getTotalWords());
  ASSERT_EQUALS(10, w.getNumUniqueWords());
  ASSERT_EQUALS(3, w.getWordCount("b"));
  ASSERT_EQUALS(1, w.getWordCount("a"));
  ASSERT_EQUALS(1, w.getWordCount("c"));
  ASSERT_EQUALS(1, w.getWordCount(" d"));
  ASSERT_EQUALS(6, w.getWordCount("x"));
  ASSERT_EQUALS(6, w.getWordCount("y"));
  ASSERT_EQUALS(6, w.getWordCount("z"));
  ASSERT_EQUALS(7, w.getWordCount("bread"));
  ASSERT_EQUALS(7, w.getWordCount("tastes"));
  ASSERT_EQUALS(7, w.getWordCount("good"));

  cout << "Testing dumpWordsSortedByWord below:" << endl;
  stringstream ss;
  w.dumpWordsSortedByWord(ss);
  string expectedOutput = "A,1\nB,3\nBREAD,7\nC,1\nD,1\nGOOD,7\nTASTES,7\nX,6\nY,6\nZ,6\n";
  string actualOutput = ss.str();
  ASSERT_EQUALS(expectedOutput,actualOutput);
 
  cout << "Testing dumpWordsSortedByOccurence below:" << endl;
  stringstream ss2;
  w.dumpWordsSortedByOccurence(ss2);
  string expectedOutput2 = "BREAD,7\nGOOD,7\nTASTES,7\nX,6\nY,6\nZ,6\nB,3\nA,1\nC,1\nD,1\n";
  string actualOutput2 = ss2.str();
  ASSERT_EQUALS(expectedOutput2,actualOutput2);
 
  return 0;
}
