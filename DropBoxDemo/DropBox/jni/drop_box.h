#include <string>

#include <cpprest/asyncrt_utils.h>
#include <pplx/pplxtasks.h>

namespace dropbox_utilities
{

// Uploads specified file to Dropbox with given name.
pplx::task<utility::string_t> upload_to_dropbox(
		const utility::string_t &localFile,
		const utility::string_t &remoteFileName);

}
