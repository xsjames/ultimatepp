#include "Core.h"

NAMESPACE_UPP

static Tuple2<const char *, const char *> sEXT_MIME[] = {
	{ "txt", "text/plain" },
	{ "html", "text/html" },
	{ "jpeg", "image/jpeg" },
	{ "eml", "message/rfc822" },
	{ "tiff", "image/tiff" },
	{ "xls", "application/vnd.ms-excel" },

	{ "323", "text/h323" },
	{ "acx", "application/internet-property-stream" },
	{ "ai", "application/postscript" },
	{ "aif", "audio/x-aiff" },
	{ "aifc", "audio/x-aiff" },
	{ "aiff", "audio/x-aiff" },
	{ "asf", "video/x-ms-asf" },
	{ "asr", "video/x-ms-asf" },
	{ "asx", "video/x-ms-asf" },
	{ "au", "audio/basic" },
	{ "avi", "video/x-msvideo" },
	{ "axs", "application/olescript" },
	{ "bas", "text/plain" },
	{ "bcpio", "application/x-bcpio" },
	{ "bin", "application/octet-stream" },
	{ "bmp", "image/bmp" },
	{ "c", "text/plain" },
	{ "cat", "application/vnd.ms-pkiseccat" },
	{ "cdf", "application/x-netcdf" },
	{ "cer", "application/x-x509-ca-cert" },
	{ "class", "application/octet-stream" },
	{ "clp", "application/x-msclip" },
	{ "cmx", "image/x-cmx" },
	{ "cod", "image/cis-cod" },
	{ "cpio", "application/x-cpio" },
	{ "crd", "application/x-mscardfile" },
	{ "crl", "application/pkix-crl" },
	{ "crt", "application/x-x509-ca-cert" },
	{ "csh", "application/x-csh" },
	{ "css", "text/css" },
	{ "dcr", "application/x-director" },
	{ "der", "application/x-x509-ca-cert" },
	{ "dir", "application/x-director" },
	{ "dll", "application/x-msdownload" },
	{ "dms", "application/octet-stream" },
	{ "doc", "application/msword" },
	{ "dot", "application/msword" },
	{ "dvi", "application/x-dvi" },
	{ "dxr", "application/x-director" },
	{ "eps", "application/postscript" },
	{ "etx", "text/x-setext" },
	{ "evy", "application/envoy" },
	{ "exe", "application/octet-stream" },
	{ "fif", "application/fractals" },
	{ "flr", "x-world/x-vrml" },
	{ "gif", "image/gif" },
	{ "gtar", "application/x-gtar" },
	{ "gz", "application/x-gzip" },
	{ "h", "text/plain" },
	{ "hdf", "application/x-hdf" },
	{ "hlp", "application/winhlp" },
	{ "hqx", "application/mac-binhex40" },
	{ "hta", "application/hta" },
	{ "htc", "text/x-component" },
	{ "htm", "text/html" },
	{ "htt", "text/webviewhtml" },
	{ "ico", "image/x-icon" },
	{ "ief", "image/ief" },
	{ "iii", "application/x-iphone" },
	{ "ins", "application/x-internet-signup" },
	{ "isp", "application/x-internet-signup" },
	{ "jfif", "image/pipeg" },
	{ "jpe", "image/jpeg" },
	{ "jpg", "image/jpeg" },
	{ "js", "application/x-javascript" },
	{ "latex", "application/x-latex" },
	{ "lha", "application/octet-stream" },
	{ "lsf", "video/x-la-asf" },
	{ "lsx", "video/x-la-asf" },
	{ "lzh", "application/octet-stream" },
	{ "m13", "application/x-msmediaview" },
	{ "m14", "application/x-msmediaview" },
	{ "m3u", "audio/x-mpegurl" },
	{ "man", "application/x-troff-man" },
	{ "mdb", "application/x-msaccess" },
	{ "me", "application/x-troff-me" },
	{ "mht", "message/rfc822" },
	{ "mhtml", "message/rfc822" },
	{ "mid", "audio/mid" },
	{ "mny", "application/x-msmoney" },
	{ "mov", "video/quicktime" },
	{ "movie", "video/x-sgi-movie" },
	{ "mp2", "video/mpeg" },
	{ "mp3", "audio/mpeg" },
	{ "mpa", "video/mpeg" },
	{ "mpe", "video/mpeg" },
	{ "mpeg", "video/mpeg" },
	{ "mpg", "video/mpeg" },
	{ "mpp", "application/vnd.ms-project" },
	{ "mpv2", "video/mpeg" },
	{ "ms", "application/x-troff-ms" },
	{ "msg", "application/vnd.ms-outlook" },
	{ "mvb", "application/x-msmediaview" },
	{ "nc", "application/x-netcdf" },
	{ "nws", "message/rfc822" },
	{ "oda", "application/oda" },
	{ "p10", "application/pkcs10" },
	{ "p12", "application/x-pkcs12" },
	{ "p7b", "application/x-pkcs7-certificates" },
	{ "p7c", "application/x-pkcs7-mime" },
	{ "p7m", "application/x-pkcs7-mime" },
	{ "p7r", "application/x-pkcs7-certreqresp" },
	{ "p7s", "application/x-pkcs7-signature" },
	{ "pbm", "image/x-portable-bitmap" },
	{ "pdf", "application/pdf" },
	{ "pfx", "application/x-pkcs12" },
	{ "pgm", "image/x-portable-graymap" },
	{ "pko", "application/ynd.ms-pkipko" },
	{ "pma", "application/x-perfmon" },
	{ "pmc", "application/x-perfmon" },
	{ "pml", "application/x-perfmon" },
	{ "pmr", "application/x-perfmon" },
	{ "pmw", "application/x-perfmon" },
	{ "pnm", "image/x-portable-anymap" },
	{ "pot", "application/vnd.ms-powerpoint" },
	{ "ppm", "image/x-portable-pixmap" },
	{ "pps", "application/vnd.ms-powerpoint" },
	{ "ppt", "application/vnd.ms-powerpoint" },
	{ "prf", "application/pics-rules" },
	{ "ps", "application/postscript" },
	{ "pub", "application/x-mspublisher" },
	{ "qt", "video/quicktime" },
	{ "ra", "audio/x-pn-realaudio" },
	{ "ram", "audio/x-pn-realaudio" },
	{ "ras", "image/x-cmu-raster" },
	{ "rgb", "image/x-rgb" },
	{ "rmi", "audio/mid" },
	{ "roff", "application/x-troff" },
	{ "rtf", "application/rtf" },
	{ "rtx", "text/richtext" },
	{ "scd", "application/x-msschedule" },
	{ "sct", "text/scriptlet" },
	{ "setpay", "application/set-payment-initiation" },
	{ "setreg", "application/set-registration-initiation" },
	{ "sh", "application/x-sh" },
	{ "shar", "application/x-shar" },
	{ "sit", "application/x-stuffit" },
	{ "snd", "audio/basic" },
	{ "spc", "application/x-pkcs7-certificates" },
	{ "spl", "application/futuresplash" },
	{ "src", "application/x-wais-source" },
	{ "sst", "application/vnd.ms-pkicertstore" },
	{ "stl", "application/vnd.ms-pkistl" },
	{ "stm", "text/html" },
	{ "sv4cpio", "application/x-sv4cpio" },
	{ "sv4crc", "application/x-sv4crc" },
	{ "svg", "image/svg+xml" },
	{ "swf", "application/x-shockwave-flash" },
	{ "t", "application/x-troff" },
	{ "tar", "application/x-tar" },
	{ "tcl", "application/x-tcl" },
	{ "tex", "application/x-tex" },
	{ "texi", "application/x-texinfo" },
	{ "texinfo", "application/x-texinfo" },
	{ "tgz", "application/x-compressed" },
	{ "tif", "image/tiff" },
	{ "tr", "application/x-troff" },
	{ "trm", "application/x-msterminal" },
	{ "tsv", "text/tab-separated-values" },
	{ "uls", "text/iuls" },
	{ "ustar", "application/x-ustar" },
	{ "vcf", "text/x-vcard" },
	{ "vrml", "x-world/x-vrml" },
	{ "wav", "audio/x-wav" },
	{ "wcm", "application/vnd.ms-works" },
	{ "wdb", "application/vnd.ms-works" },
	{ "wks", "application/vnd.ms-works" },
	{ "wmf", "application/x-msmetafile" },
	{ "wps", "application/vnd.ms-works" },
	{ "wri", "application/x-mswrite" },
	{ "wrl", "x-world/x-vrml" },
	{ "wrz", "x-world/x-vrml" },
	{ "xaf", "x-world/x-vrml" },
	{ "xbm", "image/x-xbitmap" },
	{ "xla", "application/vnd.ms-excel" },
	{ "xlc", "application/vnd.ms-excel" },
	{ "xlm", "application/vnd.ms-excel" },
	{ "xlt", "application/vnd.ms-excel" },
	{ "xlw", "application/vnd.ms-excel" },
	{ "xof", "x-world/x-vrml" },
	{ "xpm", "image/x-xpixmap" },
	{ "xwd", "image/x-xwindowdump" },
	{ "z", "application/x-compress" },
	{ "zip", "application/zip" },
};

static const Index<String>& sEXT()
{
	static Index<String> x;
	ONCELOCK {
		for(int i = 0; i < __countof(sEXT_MIME); i++)
			x.Add(sEXT_MIME[i].a);
	}
	return x;
}

static const Index<String>& sMIME()
{
	static Index<String> x;
	ONCELOCK {
		for(int i = 0; i < __countof(sEXT_MIME); i++)
			x.Add(sEXT_MIME[i].b);
	}
	return x;
}

const Index<String>& GetMIMETypes() {
	static Index<String> x;
	ONCELOCK {
		const Index<String>& h = sMIME();
		for(int i = 0; i < h.GetCount(); i++)
			x.FindAdd(h[i]);
	}
	return x;
}

String FileExtToMIME(const String& ext)
{
	int q = sEXT().Find(ToLower(ext));
	return q >= 0 ? sMIME()[q] : "application/octet-stream";
}

String MIMEToFileExt(const String& mime)
{
	int q = sMIME().Find(ToLower(mime));
	return q >= 0 ? sEXT()[q] : "bin";
}

END_UPP_NAMESPACE
