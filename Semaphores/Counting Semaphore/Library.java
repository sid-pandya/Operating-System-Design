// For this Counting Semaphore demo, we are creating a library of books. 
// One book can be issued to only one reader at a time. The other readers
// can get books only when the more books are available or the books are
// retuned back to library by the readers who has already issued.
// The number of readers is more than the number of books in our scenario.
// What all we want is issue the books to readers if available otherwise
// hold on till the books are retuned back to the library. 

// This example is taken from:
// http://www.concretepage.com/java/java-counting-and-binary-semaphore-tutorial-with-example#counting-semaphore


import java.util.concurrent.Semaphore;

public class Library {
	   private static final int MAX_PERMIT = 3;
	   private final Semaphore availableBook = new Semaphore(MAX_PERMIT, true);
	   private Book[] books = {new Book("Ramayan"), new Book("Mahabharat"), new Book("Panchtantra")};
	   private boolean[] beingRead = new boolean[MAX_PERMIT];
	   
	   //Book is being issued to reader
	   public Object issueBook() throws InterruptedException {
	     availableBook.acquire();
	     return getNextAvailableBook();
	   }
	   private synchronized Book getNextAvailableBook() {
	     Book book = null;  
	     for (int i = 0; i < MAX_PERMIT; ++i) {
	       if (!beingRead[i]) {
	          beingRead[i] = true;
	          book = books[i];
	          System.out.println(book.getBookName()+" has been issued.");
	          break;
	       }
	     }
	     return book;
	   }

	   //Book is being returned to library
	   public void returnBook(Book book) {
		     if (markAsAvailableBook(book))
		       availableBook.release();
	   }	   
	   private synchronized boolean markAsAvailableBook(Book book) {
	     boolean flag = false;  
	     for (int i = 0; i < MAX_PERMIT; ++i) {
	       if (book == books[i]) {
	          if (beingRead[i]) {
	            beingRead[i] = false;
	            flag = true;
		        System.out.println(book.getBookName()+" has been returned.");
	          } 
	          break;
	       }
	     }
	     return flag;
	   }
} 
