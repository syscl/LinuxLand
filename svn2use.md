# svn usage

```sh
svn checkout --username=syscl svn+ssh://syscl@svn.code.sf.net/p/clove
svn commit -m "Change information here"
```
- if you added some files to the working copy do
```sh
svn add /path/to/file /path/to/otherfile
```
or
```sh
svn add /path/to/dir --force
```
and finally
```sh
svn commit -m "who did what why"
```
