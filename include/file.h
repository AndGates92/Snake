#ifndef FILE_H
#define FILE_H
/**
 * @copyright
 * @file file.h
 * @author Andrea Gianarda
 * @date 06th of February 2019
 * @brief File handling header file
*/

#include <fstream>

namespace iofile {

	/** @defgroup FileGroup File Doxygen Group
	 *  File functions and classes
	 *  @{
	 */

	namespace {
		/**
		 * @brief If file doesn't have read or write permission, it will be redirected to /dev/null for such operation
		 *
		 */
		const static std::string & null_file("/dev/null");
	}
	/**
	 * @brief Access mode
	 *
	 */
	typedef enum class mode_list {
		RO, /**< Read-only */
		WO, /**< Write-only */
		RW, /**< Read-write */
		NO_ACCESS, /**< No access */
	} mode_e;

	/**
	 * @brief Function: std::ostream& operator<< (std::ostream& os, iofile::mode_e mode)
	 *
	 * \param os: output stream
	 * \param mode: direction to be printed
	 *
	 * Overload << operator to print access mode 
	 */
	std::ostream& operator<< (std::ostream& os, iofile::mode_e mode);

	class File {
		public:
			// Constructor
			/**
			 * @brief Function: File(std::string const & filename = "", mode_e access_mode = iofile::mode_e::NO_ACCESS)
			 *
			 * \param filename: name fo the file
			 * \param access_mode: permission to the file
			 *
			 * File constructor
			 */
			File(std::string const & filename = "", mode_e access_mode = iofile::mode_e::NO_ACCESS): name(filename), mode(access_mode) {
				set_access_flags();
			};

			// Destructor
			/**
			 * @brief Function: ~File()
			 *
			 * Destructor of File
			 */
			~File();

			// Set functions
			void set_filename(std::string filename);
			void set_access_mode(iofile::mode_e access_mode);

			// Get functions
			std::string get_name();
			iofile::mode_e get_access_mode();
			std::ifstream & get_ifile();

			// Output stream (Write)
			void close_ofile();
			void open_ofile();
			bool ofile_is_open();

			template <typename str_type>
			void write_ofile(str_type str);

			template <typename first_str_type, typename... other_str_type>
			void write_ofile(first_str_type first_str, other_str_type ... str);

			// Input stream (Read)
			void close_ifile();
			void open_ifile();
			bool ifile_is_open();

		private:
			std::string name;
			std::ofstream ofile;
			std::ifstream ifile;
			iofile::mode_e mode;
			bool read_flag;
			bool write_flag;
			void set_read_access();
			void set_write_access();

		protected:
			void set_access_flags();
	};
	/** @} */ // End of FileGroup group
}

// ================================================================
// Output stream (write)
// ================================================================

template <typename str_type>
void iofile::File::write_ofile(str_type str) {
	if (this->write_flag == true) {
		if (this->ofile_is_open() == false) {
			// Automatically try to open ofile if still closed
			this->open_ofile();
		}
		this->ofile << str;
	}
}

template <typename first_str_type, typename... other_str_type>
void iofile::File::write_ofile(first_str_type first_str, other_str_type ... str) {
	if (this->write_flag == true) {
		if (this->ofile_is_open() == false) {
			// Automatically try to open ofile if still closed
			this->open_ofile();
		}
		this->ofile << first_str;
		this->write_ofile(str...);
	}
}
#endif // FILE_H
