#include "fileprocessor.hpp"
#include <qlogging.h>
#include <qmessagebox.h>
#include <QFileDialog>
#include <QMessageBox>
#include <QObject>

FileProcessor::FileProcessor(DataModel* model) : m_data(model) {}

void FileProcessor::read_file(const std::string& filename) {}

void FileProcessor::write_file(const std::string& filename) {}

void FileProcessor::open() {}

void FileProcessor::save() {}

void FileProcessor::save_as() {}
