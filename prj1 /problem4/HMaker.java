package hmaker;
import ham.*;
public class HMaker extends Thread {   

public int num;



     void make()                       
     {
         synchronized(Ham.box)
         {
             Ham.production++;
             System.out.println("Cook ["+num+"] make a burger.");
             
             Ham.box.notify();         
         }
     }
     public void run()
     {
         while(Ham.production<Ham.totalMaterial)  
         {
             try
             {
                 sleep(3000);
             }catch(InterruptedException ie){}
             make();                             
         }
     }
}
