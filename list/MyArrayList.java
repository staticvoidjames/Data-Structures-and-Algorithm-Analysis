public class MyArrayList{
	
	private Object[] elementData;
	private int size;
	
	public int size(){
		return size;
	}
	
	public boolean isEmpty(){
		return size == 0;
	}
	
	public MyArrayList(){
		this(10);
	}
	
	public MyArrayList(int initialCapacity){
		if(initialCapacity < 0){
			throw new IllegalArgumentException("表长度不能<0");
		}
		elementData = new Object[initialCapacity];
	}
	
	public void add(Object obj){
		if(size == elementData.length){
			Object[] newArray = new Object[size * 2 + 1];
			System.arraycopy(elementData,0,newArray,0,elementData.length);
			elementData = newArray;
		}
		
		elementData[size++] = obj;
	}
	
	public Object get(int index){
		rangeCheck(index);
		return elementData[index];
	}
	
	public void remove(int index){
		rangeCheck(index);
		int numMoved = size - index - 1;
		if(numMoved > 0){
			System.arraycopy(elementData,index + 1,elementData,index,
					numMoved);
		}
		elementData[--size] = null;
	}
	
	public void remove(Object obj){
		for(int i = 0;i < size;i++){
			if(get(i).equals(obj)){
				remove(i);
			}
		}
	}
	
	public Object set(int index,Object obj){
		rangeCheck(index);
		
		Object oldValue = elementData[index];
		elementData[index] = obj;
		return oldValue;
	}
	
	public void add(int index,Object obj){
		rangeCheck(index);
		ensureCapacity();
		System.arraycopy(elementData,index,elementData,index + 1,
				size - index);
		elementData[index] = obj;
		size++;
	}
	
	private void ensureCapacity(){
		if(size == elementData.length){
			Object[] newArray = new Object[size * 2 + 1];
			System.arraycopy(elementData,0,newArray,0,elementData.length);
			elementData = newArray;
		}
	}
	
	private void rangeCheck(int index){
		if(index < 0 || index >= size){
			try{
				throw new Exception();
			}catch(Exception e){
				e.printStackTrace();
			}
		}
	}
	
	public static void main(String[] args){
		MyArrayList list = new MyArrayList(10);
		System.out.println(list.isEmpty());
		for(int i = 0;i < 5;i++){
			list.add(i);
		}
		list.add("sss");
		list.add("aa");
		for(int i = 0;i < 7;i++){
			System.out.println(list.get(i));
		}
		list.remove(2);
		for(int i = 0;i < list.size();i++){
			System.out.println(list.get(i));
		}
	}
	
}
