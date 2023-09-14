public class javaMain
{
	static {
		System.out.println(System.getProperty("java.library.path"));
		System.loadLibrary("LAB3_impl");
	}
	public static native int add(int a, int b);

	public static void main(String[] args) 
	{
		System.out.printf("HW! add(10, 20): %d\n", add(20,30));
	}
}