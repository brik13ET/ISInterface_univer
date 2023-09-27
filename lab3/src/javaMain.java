public class javaMain
{
	static {
		System.loadLibrary("LAB3_impl");
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

	public static void main(String[] args) 
	{
		boolean ok = javaMain.init("lo");
		System.out.printf("init: %d\n", ok);
		ok = 0 < javaMain.sendTo(
			new byte[]
			{
				(byte)0xAA,
				(byte)0xBB,
				(byte)0xCC,
				(byte)0xDD,
				(byte)0xEE,
				(byte)0xFF
			}
		);
		System.out.printf("sendTo: %d\n", ok);
		var buf = javaMain.recvFrom(
			new byte[]
			{
				(byte)0xAA,
				(byte)0xBB
			},
			0
		);
		ok = buf != null;
		System.out.printf("recvFrom: %d\n", ok);
		javaMain.deinit();
	}
}