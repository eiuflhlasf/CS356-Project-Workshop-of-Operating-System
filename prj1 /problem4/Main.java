package main;
import java.io.*; import ham.*; import hmaker.*; import hassistant.*;
public class Main {
    public static void main(String[] args) {
   int a = Integer.parseInt(args[0]);
int b = Integer.parseInt(args[1]);
int c = Integer.parseInt(args[2]);
int d = Integer.parseInt(args[3]);

    int i;
    int num;
    HMaker [] maker=new HMaker [a];
for (i=0; i<a; i++){
 maker[i]=new HMaker();
         }
    HAssistant [] assistant=new HAssistant[b]; 
for (i=0; i<b; i++) {
assistant[i]=new HAssistant();
 
        }

    Ham.totalMaterial=d;
    
    System.out.println("Cooks ["+args[0]+"], Cashiers ["+args[1]+"], Customers ["+args[2]+"]");
    System.out.println("Begin run");
    
    for (i=0; i<a; i++){

         maker[i].num=i+1;
         maker[i].start();
         }
    for (i=0; i<b; i++) {

        assistant[i].num=i+1;
         num = (int)(Math.random()*(c)+1);
         assistant[i].customer_num=num; 
        assistant[i].start();
        
        }
    }
}
