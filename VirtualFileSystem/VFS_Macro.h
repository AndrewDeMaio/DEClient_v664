//////////////////////////////////////////////////////////////////////////////
/// @file VFS_Macro.h
/// @author chyaya
/// @date 2007.06.26
//////////////////////////////////////////////////////////////////////////////
#pragma once

#include <string>
#include <cstring>


//////////////////////////////////////////////////////////////////////////////
/// @fn make_unique_path
///
///   .
//////////////////////////////////////////////////////////////////////////////
inline void make_unique_path(char * s)
{
	char * d = s;
	char c;
	while(c = *s)
	{
		while((c == '/' || c == '\\') && c == s[1])
			c = *(++s);
		c = tolower(c);
		if(c == '\\') c = '/';
		*d = c;
		++s, ++d;
	}
	*d = '\0';
}


//////////////////////////////////////////////////////////////////////////////
/// @fn make_temp_filepath
///
///   .
//////////////////////////////////////////////////////////////////////////////
inline void make_temp_filepath(LPCTSTR path, LPTSTR tempPath)
{
	const char* tok = "\\/";
	char* context = nullptr;
	
	strcpy_s(tempPath, MAX_PATH, "temp/$");

	char szPathCopy[MAX_PATH];
	strcpy_s(szPathCopy, MAX_PATH, path);

	char* pFilePath = strtok_s(szPathCopy, tok, &context);
	//strcat(tempPath, strlwr(pFilePath));
	strcat_s(tempPath, MAX_PATH, pFilePath);

	while((pFilePath = strtok_s(nullptr, tok, &context)) != nullptr)
	{
		strcat_s(tempPath, MAX_PATH, "$");
		//strcat(tempPath, strlwr(pFilePath));
		strcat_s(tempPath, MAX_PATH, pFilePath);
	}
}

//////////////////////////////////////////////////////////////////////////////
/// @struct compare_path_string
///
///  string   
/// - std::map template 3  
/// - std::set template 2  
//////////////////////////////////////////////////////////////////////////////
struct compare_path_string
{
	bool operator()(const std::string& s1, const std::string& s2) const
	{
		const char * p1 = s1.c_str();
		const char * p2 = s2.c_str();

		char c1, c2;
		while((c1 = *p1) & (c2 = *p2))
		{
			while((c1 == '/' || c1 == '\\') && c1 == p1[1])
				c1 = *(++p1);
			while((c2 == '/' || c2 == '\\') && c2 == p2[1])
				c2 = *(++p2);

			c1 = tolower(c1);
			if(c1 == '\\') c1 = '/';

			c2 = tolower(c2);
			if(c2 == '\\') c2 = '/';

			if(c1 != c2) return c1 < c2;

			++p1;
			++p2;
		}

		if(!c1 && !c2)
			return false;
		else
			return c1 < c2;

	}
};



//////////////////////////////////////////////////////////////////////////////
/// @struct hash_func_path_string_stlport
///
///  string   hash function
/// - hash_map(stlport) template 3  
//////////////////////////////////////////////////////////////////////////////
struct hash_func_path_string_stlport
{ 
	size_t operator()(const std::string& s) const
	{
		unsigned long hash = 5381;
		int c;
		const char* p = s.c_str();
        
		while (c = *p)
		{
			while((c == '/' || c == '\\') && c == p[1])
				c = *(++p);
			c = tolower(c);
			if(c == '\\') c = '/';
			hash = ((hash << 5) + hash) + c;
			++p;
		}
        
        return hash;
	};
};


//////////////////////////////////////////////////////////////////////////////
/// @struct equal_path_string
///
///  string     
/// - hash_map(stlport) template 4  
//////////////////////////////////////////////////////////////////////////////
struct equal_path_string
{
	bool operator()(const std::string& s1, const std::string& s2) const
	{
		const char * p1 = s1.c_str();
		const char * p2 = s2.c_str();

		char c1, c2;
		while((c1 = *p1) & (c2 = *p2))
		{
			while((c1 == '/' || c1 == '\\') && c1 == p1[1])
				c1 = *(++p1);
			while((c2 == '/' || c2 == '\\') && c2 == p2[1])
				c2 = *(++p2);

			c1 = tolower(c1);
			if(c1 == '\\') c1 = '/';
			c2 = tolower(c2);
			if(c2 == '\\') c2 = '/';

			if(c1 != c2) return false;

			++p1;
			++p2;
		}

		if(!c1 && !c2) return true;
		return false;
	}
};


//////////////////////////////////////////////////////////////////////////////
/// @fn equal_path_string
///
/// XOR   . -__-
//////////////////////////////////////////////////////////////////////////////
inline void encrypt_data(char *data, int size, int key)
{
	//const char*	XOR_MASKING_VALUE	= "This's Korea";
	//const char* XOR_MASKING_VALUE = "chyaya";
	//const int	XOR_MASKING_SIZE	= 6;
	const char*	XOR_MASKING_VALUE	= "s2/234ESsQ^$SFT@";
	const int	XOR_MASKING_SIZE	= 16;

	if(key < 0)	key = -key;

	if(size > XOR_MASKING_SIZE)
	{
		key %= (size - XOR_MASKING_SIZE);
		
		for(int i = 0; i < XOR_MASKING_SIZE; ++i, ++key)
			data[key] ^= XOR_MASKING_VALUE[i];
	}
}


//////////////////////////////////////////////////////////////////////////////
/// @fn decode_data
///
///  .  
//////////////////////////////////////////////////////////////////////////////
inline void decode_data(char *data, int size, int key)
{
	encrypt_data(data, size, key);
}


//////////////////////////////////////////////////////////////////////////////
/// @fn calc_compress_buffer_size
///
///       .
//////////////////////////////////////////////////////////////////////////////
inline int calc_compress_buffer_size(int size)
{
	return size + (size >> 4) + 64 + 3;
}
