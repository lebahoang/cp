package main

type Node struct {
	key    string
	val    int
	before *Node
	after  *Node
}
type MinLL struct {
	root *Node
	tail *Node
}

type MaxLL struct {
	root *Node
	tail *Node
}

type AllOne struct {
	m   map[string]*Node
	min *MinLL
	max *MaxLL
}

func (this *Node) inc() {
	this.val++
}

func (this *Node) dec() {
	this.val--
}

func (this *MinLL) append(i *Node) {
	if this.root == nil {
		this.root = i
	}
	if this.tail != nil {
		this.tail.after = i
		i.before = this.tail
	}
	this.tail = i
}

func (this *MaxLL) append(i *Node) {
	if this.root == nil {
		this.root = i
	}
	if this.tail != nil {
		this.tail.after = i
		i.before = this.tail
	}
	this.tail = i
}

func (this *MinLL) update(i *Node) {
	if i.val == 0 {
		if i.before != nil {
			i.before.after = i.after
			i.after.before = i.before
		} else {
			i.after.before = nil
		}
		return
	}
	if this.root.val > i.val {
		t := this.root
		i.before.after = i.after
		i.after.before = i.before
		i.after = t
		i.before = nil
		this.root = i
	}
}

func (this *MaxLL) update(i *Node) {
	if i.val == 0 {
		if i.before != nil {
			i.before.after = i.after
			i.after.before = i.before
		} else {
			i.after.before = nil
		}
		return
	}
	if this.root.val < i.val {
		t := this.root
		i.before.after = i.after
		i.after.before = i.before
		i.after = t
		i.before = nil
		this.root = i
	}
}

func Constructor() *AllOne {
	return &AllOne{
		m:   make(map[string]*Node),
		min: &MinLL{root: nil},
		max: &MaxLL{root: nil},
	}
}

func (this *AllOne) Inc(key string) {
	i, ok := this.m[key]
	if ok {
		i.inc()
		this.min.update(i)
		this.max.update(i)
	} else {
		i = &Node{
			key:    key,
			val:    1,
			before: nil,
			after:  nil,
		}
		this.m[key] = i
		this.min.append(i)
		this.max.append(i)
	}
}

func (this *AllOne) Dec(key string) {
	i, ok := this.m[key]
	if ok {
		i.dec()
		if i.val == 0 {
			delete(this.m, key)
		}
		this.min.update(i)
		this.max.update(i)
	}
}

func (this *AllOne) GetMaxKey() string {
	return this.max.root.key
}

func (this *AllOne) GetMinKey() string {
	return this.min.root.key
}

func main() {

}
