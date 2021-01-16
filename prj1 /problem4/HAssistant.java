package hassistant;
import ham.*;
public class HAssistant extends Thread{
    
    public int num;
    public int customer_num;
    



    void sell()        
    {
        synchronized(Ham.box)
        {
            if(Ham.production==Ham.sales)
            {
                try{
                Ham.box.wait();           
                }catch(InterruptedException ie){}
            }
            Ham.sales++;
            System.out.println("Casher ["+num+"] take a burger to customor.");
            
            
        }
    }
    public void run()
    {
        while(Ham.sales<Ham.totalMaterial)
        {
        
        System.out.println(" Customer ["+customer_num+"] come.");
        
            System.out.println("Casher ["+num+"] accepts an order.");
            sell();                            
            try{
                sleep(1000);
            }catch(InterruptedException ie){}
        }
    }
}
