package ConcurrentTest;

import java.util.Random;
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.Semaphore;

import com.sun.tools.javac.jvm.Items;

import java.util.ArrayDeque;
import java.util.LinkedList;
import java.util.Queue;

public class SolutionToProCon {
	// Initiate some constances
	private final static int BUFFER_SIZE = 10;
	final static Semaphore mutex = new Semaphore(1);
	final static Semaphore items = new Semaphore(0);
	final static Semaphore spaces = new Semaphore(BUFFER_SIZE);
	static long start; // main thread sets
	
	//shared buffer and locks
	public static Queue<String> buffer = new ArrayDeque<String>(BUFFER_SIZE);;
	public static Object mutex1 = new Object();
	
	///Producer thread
	private static class Producer extends Thread {
		private Thread thread;
		private int id;
		
		Producer(int id)
		{
			this.id = id;
			
			thread = new Thread(this, "Producer[" + id + "]");
		}
		
		public void run()
		{
				
				// acquireUninterruptibly plays a role as wait
				spaces.acquireUninterruptibly();
				
				
				mutex.acquireUninterruptibly();
				long t = (System.nanoTime() - start);
				System.out.println("Producer[" + id + "]" + "-> producing @ t=" + t);
				String evenString = "product" + id;
				buffer.add(evenString);
				System.out.println("\t" + evenString + " has been added!");
				// release plays a role as signal
				mutex.release();
				
				
				items.release();
			
		}
	}
	
	///Consumer thread
	private static class Consumer extends Thread
	{
		private Thread thread;
		private int id;
		
		Consumer(int id)
		{
			this.id = id;
			thread = new Thread(this, "Consumer[" + id + "]");
		}
		
		public void run()
		{
			
			
				items.acquireUninterruptibly();
				
				mutex.acquireUninterruptibly();
				long t = (System.nanoTime() - start);
				System.out.println("Consumer[" + id + "]" + "-> producing @ t=" + t);
				buffer.remove();
				System.out.println("\tFIFO: One product has been removed!");
				mutex.release();
				
				spaces.release();
				
			
		}
	}
	
	
	public static void main(String[] args) 
	{
		final int NUMBER_OF_THREAD = 20;
		
		//start the timer (usecs)
		start = System.nanoTime();
		
		// Consume this is the physical buffer
		buffer = new LinkedList<>();
		Producer[] producers = new Producer[NUMBER_OF_THREAD];
		Consumer[] consumers = new Consumer[NUMBER_OF_THREAD];
		
		// start the simulation
		for(int i = 0; i < NUMBER_OF_THREAD; i++)
		{
			producers[i] = new Producer(i+1); 
			consumers[i] = new Consumer(i+1);
		}
		
		for(int i = 0; i < NUMBER_OF_THREAD; i++)
		{
			producers[i].start();
			consumers[i].start();
		}
		

		
		//wait for producers to finish
		for(int i = 0; i < NUMBER_OF_THREAD; i++)
		{
			try {
				producers[i].join(); 
			}
			catch (InterruptedException e) {
				e.printStackTrace(); 
			}
		}
		
		//wait for consumers to finish
		for(int i = 0; i < NUMBER_OF_THREAD; i++)
		{
			try { 
				consumers[i].join(); 
			}
			catch (InterruptedException e) {
				e.printStackTrace(); 
			}
		}
		
		// Gauge the time. Just for fun!
		long millis2 = System.nanoTime();
		
		long elapsedTime = (millis2 - start);
		System.out.println("Simulation has finished. Runtime: " + elapsedTime + "ns");
	}
}
