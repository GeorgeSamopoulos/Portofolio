#pragma once
#include <functional>
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <assert.h>
#include <cstdint>
#include <map>
#define input getinput
#define ref obj_pointer
#define key(a) data1[copys(a)]
#define object v_temp
#define func(a) data1[copys(a)]=[]()
#define lambda []()
#define let Message
#define nl std::endl
#define values vt+=
#define call(a) data1[copys(a)]="call"
#define arg(a) arg1(#a)
#define self(a) self1(#a)
#define eval_cond(a) eval_cond1(#a)
#define eval(a) eval1(#a)
#define args_list args_list1()
#define none 


class obj_val;
class value_type;
std::string object_type(value_type);
std::map<std::string, value_type> data1;
std::map<std::string, value_type> global_send_obj;
std::map<std::string, value_type> global_rec_obj;
std::string gid;
int counter = 0;
std::string copys(std::string s) {
	gid = s;
	return s;
}

enum class type {
	int_t,
	double_t,
	bool_t,
	string_t,
	object_t,
	void_f,
	int_f,
	string_f,
	bool_f,
	double_f,
	object_f
};
class value_type {
public:
	std::string id;
	std::vector<value_type> l;
	type TYPE=type::int_t;

	int i=0;
	double d=0.0;
	bool b=true;
	std::string s="";
	obj_val* obj = nullptr;
	void (*vp)() = nullptr;
	int (*ip)() = nullptr;
	std::string(*sp)() = nullptr;
	bool(*bp)() = nullptr;
	double(*dp)() = nullptr;
	obj_val* (*op)() = nullptr;

	value_type operator , (const char* s) {

		value_type temp;
		temp.s = s;
		temp.TYPE = type::string_t;
		temp.id = std::to_string(counter);
		l.push_back(temp);
		counter++;
		return *this;
	}

	value_type operator , (std::string s) {

		value_type temp;
		temp.s = s;
		temp.TYPE = type::string_t;
		temp.id = std::to_string(counter);
		l.push_back(temp);
		counter++;
		return *this;
	}

	value_type operator , (int i) {

		value_type temp;
		temp.i = i;
		temp.TYPE = type::int_t;
		temp.id = std::to_string(counter);
		l.push_back(temp);
		counter++;
		return *this;
	}

	value_type operator , (double d) {

		value_type temp;
		temp.d = d;
		temp.TYPE = type::double_t;
		temp.id = std::to_string(counter);
		l.push_back(temp);
		counter++;
		return *this;
	}

	value_type operator , (bool b) {
		value_type temp;
		temp.b = b;
		temp.TYPE = type::bool_t;
		temp.id = std::to_string(counter);
		l.push_back(temp);
		counter++;
		return *this;
	}
	
	value_type operator = (const char * x) {
		value_type temp;
		temp.TYPE = type::string_t;
		temp.id = gid;
		temp.s = x;
		return temp;
	}

	value_type operator = (std::string x) {
		value_type temp;
		temp.TYPE = type::string_t;
		temp.id = gid;
		temp.s = x;
		return temp;
	}

	public: value_type operator = (obj_val* x) {
		value_type temp;
		temp.TYPE = type::object_t;
		temp.id = gid;
		temp.obj = x;
		return temp;
	}

	public: value_type operator = (int x) {
		value_type temp;
		temp.i = x;
		temp.TYPE = type::int_t;
		temp.id = gid;
		return temp;
	}

	public: value_type operator = (bool x) {
		value_type temp;
		temp.b = x;
		temp.TYPE = type::bool_t;
		temp.id = gid;
		return temp;
	}

	public: value_type operator =(double x) {
		value_type temp;
		temp.d = x;
		temp.TYPE = type::double_t;
		temp.id = gid;
		return temp;
	}

	public: value_type operator =(void (*x)()) {
		value_type temp;
		temp.vp = x;
		temp.TYPE = type::void_f;
		temp.id = gid;
		return temp;
	}

	public: value_type operator =(int (*x)()) {
		value_type temp;
		temp.ip = x;
		temp.TYPE = type::int_f;
		temp.id = gid;
		return temp;
	}

	public: value_type operator =(bool (*x)()) {
		value_type temp;
		temp.bp = x;
		temp.TYPE = type::bool_f;
		temp.id = gid;
		return temp;
	}

	public: value_type operator =(double (*x)()) {
		value_type temp;
		temp.dp = x;
		temp.TYPE = type::double_f;
		temp.id = gid;
		return temp;
	}

	public: value_type operator =(std::string(*x)()) {

		value_type temp;
		temp.sp = x;
		temp.TYPE = type::string_f;
		temp.id = gid;
		return temp;
	}


	public: void operator =(value_type x) {

		this->i = x.i;
		this->d = x.d;
		this->b = x.b;
		this->s = x.s;

		this->l = x.l;

		this->dp = x.dp;
		this->obj = x.obj;
		this->op = x.op;
		this->ip = x.ip;
		this->sp = x.sp;
		this->bp = x.bp;
		this->vp = x.vp;
		this->dp = x.dp;


		this->TYPE = x.TYPE;
		this->id = gid;
	}

	public:value_type operator =(obj_val* (*x)()) {
		
		value_type temp;
		temp.op = x;
		temp.TYPE = type::object_f;
		temp.id = gid;
		return temp;
	}


	public:value_type operator += (int x) {
		value_type temp;
		temp.i = x;
		temp.TYPE = type::int_t;
		temp.id = std::to_string(counter);
		counter++;
		return temp;
	}

	public:value_type operator += (double x) {

		value_type temp;
		temp.d = x;
		temp.TYPE = type::double_t;
		temp.id = std::to_string(counter);
		counter++;
		return temp;
	}

	public:value_type operator += (bool x) {

		value_type temp;
		temp.b = x;
		temp.TYPE = type::bool_t;
		temp.id = std::to_string(counter);
		counter++;
		return temp;
	}

	public:value_type operator += (const char* x) {

		value_type temp;
		temp.s = x;
		temp.TYPE = type::string_t;
		temp.id = std::to_string(counter);
		counter++;
		return temp;
	}

	public:value_type operator += (std::string x) {

		value_type temp;
		temp.s = x;
		temp.TYPE = type::string_t;
		temp.id = std::to_string(counter);
		counter++;
		return temp;
	}

	public: value_type operator , (value_type x2) {
		this->l.push_back(*this);
		x2.l = this->l;
		return x2;
	}
	
	friend bool operator ==(value_type x, value_type y) {

		if (x.TYPE != y.TYPE) {
			assert(0);
		}
		if (x.TYPE == type::string_t) {
			return y.s.compare(x.s) == 0;
		}
		if (x.TYPE == type::int_t) {
			return y.i == x.i;
		}
		if (x.TYPE == type::bool_t) {
			return y.b == x.b;
		}
		if (x.TYPE == type::int_t) {
			return y.i == x.i;
		}
		assert(0);
		return false;
	}
	friend bool operator !=(value_type x, value_type y) {

		if (x.TYPE != y.TYPE) {
			assert(0);
		}
		if (x.TYPE == type::string_t) {
			return y.s.compare(x.s) != 0;
		}
		if (x.TYPE == type::int_t) {
			return y.i != x.i;
		}
		if (x.TYPE == type::bool_t) {
			return y.b != x.b;
		}
		if (x.TYPE == type::int_t) {
			return y.i != x.i;
		}
		assert(0);
		return false;
	}
	friend double operator +(value_type x, value_type y) {

		if (x.TYPE == type::double_t && y.TYPE==type::double_t) {
			return x.d + y.d;
		}
		if (x.TYPE == type::int_t && y.TYPE == type::int_t) {
			return (double)x.i + (double)y.i;
		}
		if (x.TYPE == type::double_t && y.TYPE == type::int_t) {
			return x.d + (double)y.i;
		}
		if (x.TYPE == type::int_t && y.TYPE == type::double_t) {
			return (double)x.d + y.i;
		}
		assert(0);
		return false;
	}
	friend double operator -(value_type x, value_type y) {

		if (x.TYPE == type::double_t && y.TYPE == type::double_t) {
			return x.d - y.d;
		}
		if (x.TYPE == type::int_t && y.TYPE == type::int_t) {
			return (double)x.i - (double)y.i;
		}
		if (x.TYPE == type::double_t && y.TYPE == type::int_t) {
			return x.d - (double)y.i;
		}
		if (x.TYPE == type::int_t && y.TYPE == type::double_t) {
			return (double)x.d - y.i;
		}
		assert(0);
		return false;
	}
	friend double operator *(value_type x, value_type y) {

		if (x.TYPE == type::double_t && y.TYPE == type::double_t) {
			return x.d *y.d;
		}
		if (x.TYPE == type::int_t && y.TYPE == type::int_t) {
			return (double)x.i *(double)y.i;
		}
		if (x.TYPE == type::double_t && y.TYPE == type::int_t) {
			return x.d * (double)y.i;
		}
		if (x.TYPE == type::int_t && y.TYPE == type::double_t) {
			return (double)x.d * y.i;
		}
		assert(0);
		return false;
	}
	friend double operator /(value_type x, value_type y) {

		if (x.TYPE == type::double_t && y.TYPE == type::double_t) {
			return x.d / y.d;
		}
		if (x.TYPE == type::int_t && y.TYPE == type::int_t) {
			return (double)x.i / (double)y.i;
		}
		if (x.TYPE == type::double_t && y.TYPE == type::int_t) {
			return x.d / (double)y.i;
		}
		if (x.TYPE == type::int_t && y.TYPE == type::double_t) {
			return (double)x.d / y.i;
		}
		assert(0);
		return false;
	}

	friend std::ostream& operator << (std::ostream& os, const value_type x) {
		if (x.TYPE == type::int_t) {
			os << x.i;
		}
		else if (x.TYPE == type::double_t) {
			os << x.d;
		}
		else if (x.TYPE == type::string_t) {

			os << x.s;
		}
		else if (x.TYPE == type::bool_t) {
			os << x.b;
		}
		else if (x.TYPE == type::object_t) {
			os << object_type(x);
		}
		else {
			os << "method";
		}
		return os;
	}
	void clear() {
		*this = new value_type;
	}
};

value_type v1;
class obj_val {
public:
	std::map<std::string, value_type> data;
	//std::map<std::string, value_type> args;
	obj_val() {

	}
	obj_val(obj_val* x) {
		*this = x;
	}


	obj_val* operator [] (value_type v) {
		counter = 0;
		v.l.push_back(v);
		obj_val* temp = new obj_val;
		for (unsigned int i = 0; i < v.l.size(); i++) {
			temp->data[v.l.at(i).id] = v.l.at(i);
		}
		return temp;

	}


};

class value {
public:
	value_type* v;
	void operator = (std::string x) {
		v->clear();
		v->TYPE = type::string_t;
		v->s = x;
	}

	void operator = (const char * x) {
		v->clear();
		v->TYPE = type::string_t;
		v->s = x;
	}

	void operator = (int x) {
		v->clear();
		v->TYPE = type::int_t;
		v->i = x;
	}

	void operator = (double x) {
		v->clear();
		v->TYPE = type::double_t;
		v->d = x;
	}

	void operator = (bool x) {
		v->clear();
		v->TYPE = type::bool_t;
		v->b = x;
	}

	void operator = (value_type nv) {
		*v = nv;
	}
	
	friend std::ostream& operator << (std::ostream& os, value x) {
		if (x.v->TYPE == type::int_t) {
			os << x.v->i;
		}
		else if (x.v->TYPE == type::double_t) {
			os << x.v->d;
		}
		else if (x.v->TYPE == type::string_t) {

			os << x.v->s;
		}
		else if (x.v->TYPE == type::bool_t) {
			os << x.v->b;
		}
		else if (x.v->TYPE == type::object_t) {
			os << object_type(*(x.v));
		}
		else {
			os << "method";
		}
		return os;
	}
	
};
class Message {
public:
	obj_val* send_obj;
	obj_val* rec_obj;
	bool isSending = true;
	Message(obj_val x) {
		send_obj = NULL;
		rec_obj = NULL;
	}
	Message(obj_val* x) {
		send_obj = x;
		rec_obj = NULL;
	}

	Message() {
		send_obj = NULL;
		rec_obj = NULL;
	}

	value operator [](std::string s){
		value* x = new value;
		if (isSending==true) {
			x->v = &send_obj->data[s];
		}else {
			x->v = &rec_obj->data[s];
		}
		return *x;
	}

	Message operator = (obj_val obj) {
		obj_val temp = obj;
		this->send_obj = &temp;
		return *this;
	}
	Message operator = (obj_val* obj) {

		this->send_obj->data = obj->data;
		return *this;
	}

	friend std::ostream& operator << (std::ostream& os, const Message mes) {
		  os << "object [";
		  obj_val* dp;
		  if (mes.isSending==true) {
			  dp = mes.send_obj;
		  }else {
			dp = mes.rec_obj;
		  }
		  obj_val dt = *dp;
		  for (auto& p : dt.data) {
			  os << " \"" << p.first << "\":";
			  if (p.second.TYPE == type::int_t) {
				  os << p.second.i;
			  }
			  else if (p.second.TYPE == type::double_t) {
				  os << p.second.d;
			  }
			  else if (p.second.TYPE == type::string_t) {
				  
				  os << p.second.s;
			  }
			  else if (p.second.TYPE == type::bool_t) {
				  os << p.second.b;
			  }
			  else if (p.second.TYPE == type::object_t) {
				  os << object_type(p.second);
			  }
			  else {
				  os << "method";
			  }

			  os << " ,";
		  }
		  os << '\b' << "]" << std::endl;
		  return os;
	  }
	  
	Message operator << (const Message mes) {
		if (mes.isSending==true) {
			this->isSending = false;
			this->rec_obj = this->send_obj;
			this->send_obj = mes.send_obj;
			int call_found = false;
			std::string call_func;
			for (auto& p : this->send_obj->data) {
				if (p.second.s=="call") {
					call_found = true;
					call_func = p.first;
				}
				
			}
			if (call_found==false) {
				assert(0);
			}
			switch (this->rec_obj->data[call_func].TYPE){
				case type::bool_f:
					global_send_obj =this->send_obj->data;
					global_rec_obj = this->rec_obj->data;
					 this->rec_obj->data[call_func].bp();
				case type::void_f:
					 global_send_obj = this->send_obj->data;
					 global_rec_obj = this->rec_obj->data;
					this->rec_obj->data[call_func].vp();
					break;
				case type::int_f:
					global_send_obj = this->send_obj->data;
					global_rec_obj = this->rec_obj->data;
					this->rec_obj->data[call_func].ip();
					break;
				case type::double_f:
					global_send_obj = this->send_obj->data;
					global_rec_obj = this->rec_obj->data;
					 this->rec_obj->data[call_func].dp();
					 break;
				case type::string_f:
					global_send_obj = this->send_obj->data;
					global_rec_obj = this->rec_obj->data;
					 this->rec_obj->data[call_func].sp();
					 break;
				case type::object_f:
					global_send_obj = this->send_obj->data;
					global_rec_obj = this->rec_obj->data;
					 this->rec_obj->data[call_func].op();
					 break;
				default:
					assert(0);
			}
		}else {
			assert(0);
		}
 		return *this;
	}
};

std::string object_type(value_type v) {
	std::string s = "object[ ";
	obj_val* o = v.obj;
	obj_val ob = *o;
	for (auto& x : ob.data) {
		s += "\"" + x.first + "\"" + ":";
		if (x.second.TYPE == type::int_t) {
			s += std::to_string(x.second.i);

		}
		else if (x.second.TYPE == type::double_t) {
			s += std::to_string(x.second.d);
		}
		else if (x.second.TYPE == type::string_t) {
			
			s += x.second.s;
		}
		else if (x.second.TYPE == type::bool_t) {
			s += std::to_string(x.second.b);
		}
		else if (x.second.TYPE == type::object_t) {
			s += object_type(x.second);
		}
		else {
			s += "method";
		}
		s += ",";
	}
	s = s.substr(0, s.size() - 1);
	s += " ]";
	return s;
}

value_type getinput(std::string msg) {
	std::cout << msg << std::endl;
	std::string x;
	std::cin >> x;
	value_type v;
	//bool
	if (x == "true") {
		v = true;
		v.TYPE = type::bool_t;
		return v;
	}
	else if (x == "false") {
		v = false;
		v.TYPE = type::bool_t;
		return v;
	}

	//number
	bool flag = true;
	bool dflag = false;
	for (char a : x) {
		if (std::isdigit(a) == false) {
			if (dflag == false && a == '.') {
				dflag = true;
			}
			else {
				flag = false;
			}
		}
	}
	if (flag == true) {
		if (dflag == true) {
			v.TYPE = type::double_t;
			double d = std::stod(x);
			v = d;
		}
		else {
			v.TYPE = type::int_t;
			int i = std::stoi(x);
			v = i;

		}
		return v;
	}
	//string
	v = x;
	v.TYPE = type::string_t;
	return v;
}

obj_val* obj_pointer(obj_val v) {
	obj_val* pntr = &v;
	return pntr;
}
value_type vt;
obj_val v_temp;


value_type self1(std::string x) {
	value_type temp= global_send_obj[x];
	return temp;
}

value_type arg1(std::string x) {
	value_type temp = global_rec_obj[x];
	return temp;
}

void eval1(std::string id) {
	if (global_send_obj[id].TYPE == type::int_t
		|| global_send_obj[id].TYPE == type::double_t
		|| global_send_obj[id].TYPE == type::bool_t
		|| global_send_obj[id].TYPE == type::string_t
		|| global_send_obj[id].TYPE == type::object_t) {
		assert(0);
	}
	global_send_obj[id].vp();
	return;
}

bool eval_cond1(std::string id) {
	if (global_send_obj[id].TYPE != type::bool_f) {
		assert(0);
	}
	bool tmp = global_send_obj[id].bp();
	return tmp;
}

std::vector<value_type> args_list1() {
	std::vector<value_type> temp;
	for (auto&t: global_send_obj) {
		if (t.second.TYPE==type::string_t && t.second.s.compare("call")==0) {
			continue;
		}
		temp.push_back(t.second);
	}
	return temp;
}

Message ref(Message x) {
	return x;
}
