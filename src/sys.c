
int fchmod(int fd, mode_t mode) {
	errno = ENOSYS;
	return -1;
}

int fchmodat(int dirfd, const char* pathname, mode_t mode, int flags) {
	errno = ENOSYS;
	return -1;
}

int symlink(const char* file, const char* linkpath) {
	errno = ENOSYS;
	return -1;
}

ssize_t readlink(const char* pathname, char* buf, size_t bufsiz) {
	errno = ENOSYS;
	return -1;
}

int truncate(const char* path, off_t length) {
	errno = ENOSYS;
	return -1;
}