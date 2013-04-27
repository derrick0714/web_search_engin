/*Author: derrick*/
#ifndef VI_FACTORY_MODEL_H
#define VI_FACTORY_MODEL_H


//////////////
//declaration 
//////////////
template < class T >
class factory
{
private:
	factory(){}
	~factory(){}
public:
	static T* instance();
private:
	static T* _obj;
};

/////////////
//definition
/////////////
template < class T >
T* factory<T>::_obj = NULL;

template < class T >
T* factory<T>::instance()
{
	if( _obj == NULL )
	{
		_obj = new T;
	}

	return _obj;
}




#endif //VI_FACTORY_MODEL_H