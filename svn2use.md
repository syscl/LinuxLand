# svn usage

Please refer also [here](http://svnbook.red-bean.com/en/1.4/svn.tour.importing.html)

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
