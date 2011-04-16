/// \brief Color holder
///
/// ColorContainer for opengl color.
/// Defaults to purple.
struct glColor {
	private:
		float r;
		float g;
		float b;
	
	public:
		inline glColor() : r(1), g(0), b(1) {};
		inline glColor(float _r, float _g, float _b) : r(_r), g(_g), b(_b) {};
		
		/// \brief Set OpenGL color to this color
		inline void Apply() const {
			glColor3f(r, g, b);
		};
};
