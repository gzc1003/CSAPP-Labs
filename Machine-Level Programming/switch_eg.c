int switch_eg(int n) {
    int result;
    switch (n) {
        
    case 0:
        result = 1;
        break;
        
    case 1:
        result = 2;
        break;
        
    case 2:
        result = 3;
        break;
        
    case 3:
        result = 10;
        break;
        
    case 4:
        result = 6;
        break;

    default:
        result = 0; 
    }
    
    return result;
}

int main()
{
    int n = 3;
    return switch_eg(n);
}