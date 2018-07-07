/**
 * 双向链表,参考jdk中的LinkedList
 */
public class MyLinkedList{
	
	private Node first;
	private Node last;
	private int size;
	
	public void add(Object obj){
		Node node;
		if(first == null){
			node = new Node(null,obj,null);
			first = node;
			last = node;
		}else{
			node = new Node(last,obj,null);
			last.next = node;
			last = node;
		}
		size++;
	}
	
	public int size(){
		return size;
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
	
	public Object get(int index){
		rangeCheck(index);
		Node temp = node(index);
		if(temp != null){
			return temp.obj;
		}
		return null;
	}
	
	public Node node(int index){
		Node temp = null;
		if(first != null){
			temp = first;
			for(int i = 0;i < index;i++){
				temp = temp.next;
			}
		}
		return temp;
	}
	
	public void remove(int index){
		Node temp = node(index);
		if(temp != null){
			Node up = temp.previous;
			Node down = temp.next;
			up.next = down;
			down.previous = up;
			size--;
		}
	}
	
	public void add(int index,Object obj){
		Node temp = node(index);
		Node newNode = new Node();
		newNode.obj = obj;
		if(temp != null){
			Node up = temp.previous;
			up.next = newNode;
			newNode.previous = up;
			newNode.next = temp;
			temp.previous = newNode;
			size++;
		}
	}
	
	class Node{
		
		Node previous;
		Object obj;
		Node next;
		
		Node(){}
		
		Node(Node previous,Object obj,Node next){
			super();
			this.previous = previous;
			this.obj = obj;
			this.next = next;
		}
		
	}
	
	public static void main(String[] args){
		MyLinkedList list = new MyLinkedList();
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
