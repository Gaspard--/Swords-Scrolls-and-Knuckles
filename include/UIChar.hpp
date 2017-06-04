#ifndef UICHAR_HPP
# define UICHAR_HPP

# include <string>

class UIChar {

	public:
		UIChar(std::string const &);
		UIChar(UIChar const &) = delete;
		UIChar(UIChar &&) = delete;
		UIChar &operator=(UIChar const &) = delete;
		UIChar &operator=(UIChar &&) = delete;
		virtual ~UIChar(void) = default;
		
		std::string getName(void) const;
		void setScore(int);
		int getScore(void) const;
		void setHealth(int);
		int getHealth(void) const;

	private:
	protected:
		std::string name;
		int score;
		int health;
};

#endif // !UICHAR_HPP
