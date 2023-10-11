public class javaMain
{
	static {
		System.loadLibrary("LAB3_impl");
		System.out.println("Static init OK");
	}
	public static native int add(int a, int b);

	// инициализирует работу с "сырыми" сокетами.
	// interfaceName - имя интерфейса, который необходимо задействовать для работы (например "eth0")
	// Возвращает true, если инициализация прошла успешно, иначе false.
	public static native boolean init(String interfaceName); 
	
	// завершает работу с сырыми сокетами, возвращает используюмую память системе.
	public static native void deinit(); 

	// отсылает через сырые сокеты буфер buf.
	// Возвращает количество посланных байт, или -1 при ошибке.
	public static native int sendTo(byte[] buf); 

	// прием первого пакета, содержимое
	// которого совпадает с buf со смещения offset. Возвращает массив присланных байт.
	public static native byte[] recvFrom(byte[] buf, int offset); 

	public static void main(String[] args) throws NoSuchFieldException, SecurityException 
	{
		System.out.println("Main()");
		boolean ok = javaMain.init("lo");
		System.out.printf("init: %b\n", ok);
		if (!ok)
		{
			System.out.println("Init failed");
			return;
		}
		int sendto_cnt = javaMain.sendTo("Алеев Ибрагим Ильясович".getBytes());
		System.out.printf("sendTo: %b\n", ok);
		var buf = javaMain.recvFrom(
			new byte[]
			{
				(byte)0xAA,
				(byte)0xBB
			},
			0
		);
		ok = buf != null;
		System.out.printf("recvFrom: %b\n", ok);
		javaMain.deinit();
	}
}