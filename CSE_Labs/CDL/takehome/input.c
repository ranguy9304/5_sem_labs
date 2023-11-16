class HelloWorld {
    public static void main(String[] args) {
        int counter;
        counter = 0;
        boolean condition; 
        condition = true;
 
        if (condition) {
            coutner=1;
        } else {
            System.out.println("Condition is false.");
        }
 
        while (counter < 10) {
            System.out.println("Counter: " + counter);
            counter = counter + 1;
        }
 
        for (int i = 0; i < 5; i++) {
            System.out.println("For loop iteration: " + i);
        }
    }
}