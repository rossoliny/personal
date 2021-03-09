#include<cstddeff>
#include<limits>
// new and delete are ok to use in general programming 
// but when we are developing a library we must give users
// the ability to control allocatoins and deallocations.
// that is why we must have additional template parameter in a 
// container so users can provide thir own allocators.
namespace isa
{
	template<>
	class allocator<void>
	{
	public:
		typedef void* pointer;
		typedef const void* const_pointer;
		typedef void value_type;
		template<typename U>
		struct rebind
		{
			typedef allocator<U> other;
		};
	};


	template<typename T>
	class allocator
	{
	public:
		using size_type = std::size_t;
		using difference_type = std::ptrdiff_t;
		using pointer = T*;
		using const_pointer = const T*;
		using reference = T&;
		using const_reference = const T&;
		using value_type = T;

		template<typename U>
		struct rebind
		{
			using other = isa::allocator<U>;
		};

		allocator() noexcept
		{
		}

		allocator(const allocator&) noexcept
		{

		}

		template<typename U>
		allocator(const allocator<U>&) noexcept
		{

		}

		~allocator()
		{

		}

		pointer address(reference x) const noexcept
		{
			return &x;
		}
		const_pointer address(const_reference x) const noexcept
		{
			return &x;
		}

		pointer allocate(size_type n, isa::allocator<void>::const_pointer hint = 0)
		{
			return reinterpret_cast<pointer> (::operator new(sizeof(T) * n));
		}

		void deallocate(pointer p, size_type n)
		{
			::operator delete (p);
		}

		size_type max_size() const noexcept
		{
			return std::numeric_limits<size_type>::max() / sizeof(T);
		}

		template<typename U, typename... Args>
		void construct(U* ptr, Args&&... args)
		{
			new (ptr) U{args};
		}

		template<typename U>
		void destroy(U* ptr)
		{
			p->~U();
		}

		inline bool operator==(allocator const&) 
		{
		   	return true; 
		}

    	bool operator!=(allocator const& a) 
		{ 
			return !operator==(a);
	   	}
	};

}

