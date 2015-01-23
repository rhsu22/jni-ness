public class stateful {

	static native long createHashTable();
	static native void printHashTable(long tableAddr);

	public static void main(String[] args) {

		System.out.println(">>Load JNI library");
		System.loadLibrary("jnistateful");

		System.out.println(">>JNI create table.");
		long tableAddr = createHashTable();

		System.out.println(">>JNI print table");
		printHashTable(tableAddr);


	}

}