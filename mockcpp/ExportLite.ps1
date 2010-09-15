# export mockcpp without boost

$env:path=$env:path+";D:\Tools\CMD\SubversionClient"

$dest_dir="D:\mockcpp_exported_new"

function export_subdir($subdir) 
{
	if (!(test-path $dest_dir\$subdir)) { mkdir $dest_dir\$subdir }
	svn export $subdir $dest_dir\$subdir --force	
}

#if (!(test-path $dest_dir\include)) { mkdir $dest_dir\include }
#svn export include $dest_dir\include --force

export_subdir include
export_subdir src
export_subdir tests

svn export --depth=files . $dest_dir --force



