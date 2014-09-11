psl1ghtv2_ports
===============

SDK: https://github.com/Estwald/PSDK3v2

Most applications need extra flags for scetool in file "$PS3DEV/ppu_rules".

SCETOOL_FLAGS	?=	-p /usr/local/ps3dev/bin/data \
			-v --sce-type=SELF --compress-data=TRUE --self-add-shdrs=TRUE --skip-sections=TRUE --key-revision=10 --self-auth-id=1010000001000003 \
			--self-add-shdrs=TRUE --self-vendor-id=01000002 --self-app-version=0001000000000000 --self-fw-version=0003006000000000 \
			--self-ctrl-flags=4000000000000000000000000000000000000000000000000000000000000000
			
