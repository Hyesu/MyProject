#pragma once

#define SAFE_DELETE(x) { \
	if(x != nullptr) { \
		delete x; \
		x = nullptr; \
	} \
}

#define DECL_SINGLETONE(x)	\
public: \
	static x* GetInstance(); \
	static void DestroyInstance(); \
	virtual ~x() {} \
private: \
	x() {} \
	static x* m_instance;

#define IMPL_SINGLETONE(x) \
x* x::m_instance = nullptr; \
x* x::GetInstance() { \
	if(m_instance == nullptr) \
		m_instance = new x(); \
	return m_instance; \
} \
void x::DestroyInstance() { \
	SAFE_DELETE(m_instance); \
}