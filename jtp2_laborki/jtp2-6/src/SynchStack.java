class SynchStack {
    int sp = 0;
    int maxSp = 100;
    int data[] = new int[maxSp];
    public void push(int i) {
	synchronized(this) {
	    data[sp++]=i;
	}
    }
    public int pop() {
	synchronized(this) {
	    return data[--sp];
	}
    }
    public SynchStack() {}
}

