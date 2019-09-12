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
#include <mutex>

/** @defgroup FileGroup File Doxygen Group
 *  File functions and classes
 *  @{
 */

namespace iofile {

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
	 * @brief Function: std::ostream& operator<< (std::ostream& os, const iofile::mode_e & mode)
	 *
	 * \param os: output stream
	 * \param mode: direction to be printed
	 *
	 * Overload << operator to print access mode 
	 */
	std::ostream& operator<< (std::ostream& os, const iofile::mode_e & mode);

	/**
	 * @brief File class
	 *
	 */
	class File {
		public:
			// Constructor
			/**
			 * @brief Function: File(std::string const & filename = "", mode_e access_mode = iofile::mode_e::NO_ACCESS)
			 *
			 * \param filename: name of the file
			 * \param access_mode: permission to the file
			 *
			 * File constructor
			 */
			explicit File(std::string const & filename = "", mode_e access_mode = iofile::mode_e::NO_ACCESS): name(filename), mode(access_mode) {
				set_access_flags();
			};

			// Destructor
			/**
			 * @brief Function: ~File()
			 *
			 * Destructor of File
			 */
			~File();

			/**
			 * @brief logging mutex
			 *
			 */
			std::mutex file_mtx;

			// Set functions
			/**
			 * @brief Function: void set_name(std::string filename)
			 *
			 * \param filename: name of the file
			 *
			 * Set filename
			 */
			void set_name(std::string filename);

			/**
			 * @brief Function: void set_access_mode(iofile::mode_e access_mode)
			 *
			 * \param access_mode: file permissions
			 *
			 * Set access permissions
			 */
			void set_access_mode(iofile::mode_e access_mode);

			// Get functions
			/**
			 * @brief Function: std::string get_name() const
			 *
			 * \return the filename
			 *
			 * Get filename
			 */
			std::string get_name() const;

			/**
			 * @brief Function: iofile::mode_e get_access_mode() const
			 *
			 * \return file permissions
			 *
			 * Get access permissions
			 */
			iofile::mode_e get_access_mode() const;

			/**
			 * @brief Function: std::ifstream & get_ifile()
			 *
			 * \return pointer to the input stream linked to the file
			 *
			 * Get input stream linked to the file
			 */
			std::ifstream & get_ifile();

			// Output stream (Write)
			/**
			 * @brief Function: void close_ofile()
			 *
			 * Close ofile - disable output stream linked to file
			 */
			void close_ofile();
			/**
			 * @brief Function: void open_ofile()
			 *
			 * Open ofile - enable output stream linked to file
			 */
			void open_ofile();
			/**
			 * @brief Function: bool ofile_is_open()
			 *
			 * \return boolean value whether ostream linked to the file can read it (true) or not (false)
			 *
			 * Check if ofile is opened
			 */
			bool ofile_is_open();

			/**
			 * @brief Function: void write_ofile(str_type str)
			 *
			 * \param str: string to write to output stream
			 *
			 * Write string to output stream
			 */
			template <typename str_type>
			void write_ofile(str_type str);

			/**
			 * @brief Function: void write_ofile(first_str_type first_str, other_str_type ... str)
			 *
			 * \param first_str: string to write to output stream
			 * \param str: remaining string to write to output stream
			 *
			 * Write recursively string to output stream
			 */
			template <typename first_str_type, typename... other_str_type>
			void write_ofile(first_str_type first_str, other_str_type ... str);

			// Input stream (Read)
			/**
			 * @brief Function: void close_ifile()
			 *
			 * Close ifile - disable input stream linked to file
			 */
			void close_ifile();
			/**
			 * @brief Function: void open_ifile()
			 *
			 * Open ifile - enable input stream linked to file
			 */
			void open_ifile();
			/**
			 * @brief Function: bool ifile_is_open()
			 *
			 * \return boolean value whether ostream linked to the file can read it (true) or not (false)
			 *
			 * Check if ifile is opened
			 */
			bool ifile_is_open();

		private:
			/**
			 * @brief Filename
			 *
			 */
			std::string name;
			/**
			 * @brief Output stream ofile
			 *
			 */
			std::ofstream ofile;
			/**
			 * @brief Input stream ifile
			 *
			 */
			std::ifstream ifile;
			/**
			 * @brief Access permissions
			 *
			 */
			iofile::mode_e mode;

			/**
			 * @brief Read flag
			 *
			 */
			bool read_flag;

			/**
			 * @brief Write flag 
			 *
			 */
			bool write_flag;

			/**
			 * @brief Function: void set_read_access()
			 *
			 * Set read permission 
			 */
			void set_read_access();

			/**
			 * @brief Function: void set_write_access()
			 *
			 * Set write permission 
			 */
			void set_write_access();

		protected:
			/**
			 * @brief Function: void set_access_flags()
			 *
			 * Set access permissions
			 */
			void set_access_flags();
	};

	/**
	 * @brief Function: std::ostream& operator<< (std::ostream& os, const iofile::File & file)
	 *
	 * \param os: output stream
	 * \param file: file whose information are to be printed
	 *
	 * Overload << operator to print file information
	 */
	std::ostream& operator<< (std::ostream& os, const iofile::File & file);

}
/** @} */ // End of FileGroup group

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
		// Flush content to ostream file
		this->ofile.flush();
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
