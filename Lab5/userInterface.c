int userInterface () {

char getButton(char i, char j) {
    if (i == 0 && j == 0) return '7';
    else if (i == 0 && j == 1) return '4';
    else if (i == 0 && j == 2) return '1';
   else if (i == 0 && j == 3) return '0';
    
   else if (i == 1 && j == 1) return '8';
    else if (i == 1 && j ==2) return '5';
    else if (i == 1 && j == 3) return 'C'
  
    else if (i == 2 && j == 0) return '9';
    else if (i == 2 && j ==1) return '6';
    else if (i == 2 && j == 2) return '3';
    else if (i == 2 && j == 3) return '=';
    
    
      
    
    else if (i == 3 && j == 0) return '+';
    else if (i == 3 && j == 2) return '-';
    else if (i == 3 && j == 0) return 'x';
    else if (i == 3 && j == 1) return '/';

}
}
