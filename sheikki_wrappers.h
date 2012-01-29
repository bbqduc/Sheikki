inline void sheikki_glBindVertexArray(GLuint array)
{
	#ifdef __APPLE__
		glBindVertexArray(array);
	#else
		glBindVertexArray(array);
	#endif
}

inline void sheikki_glGenVertexArrays(GLsizei s, GLuint* arrays)
{
	#ifdef __APPLE__
		glGenVertexArrays(s, arrays);
	#else
		glGenVertexArrays(s, arrays);
	#endif
}
